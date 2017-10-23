// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewController.h"
#include "AppLocationDelegate.h"
#include "MathFunc.h"
#include "AppDelegate.h"
#include "App.h"
#include "DeviceHelpers.h"

using namespace Eegeo::iOS;

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver: self
     selector: @selector(onPause)
     name: @"handlePause"
     object: nil];

    [[NSNotificationCenter defaultCenter] addObserver: self
     selector: @selector(onResume)
     name: @"handleResume"
     object: nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                        selector:@selector(didBecomeActive)
                                        name:UIApplicationDidBecomeActiveNotification
                                        object:nil];


    if([self respondsToSelector:@selector(setNeedsStatusBarAppearanceUpdate)])
    {
        [self setNeedsStatusBarAppearanceUpdate];
    }

    App::Initialise();
    GameDeviceType device = static_cast<GameDeviceType>(App::GetDevice());
    NSInteger preferredFramerate = ExampleApp::Helpers::DeviceHelpers::GetPreferredFramerate(device);
    [self setPreferredFramesPerSecond:preferredFramerate];
    
    m_previousTimestamp = CFAbsoluteTimeGetCurrent();
    m_pAppRunner = NULL;
    
    [self intialiseVoiceControlStuff];
}

- (void) intialiseVoiceControlStuff
{
    speechRecognizer = [[SFSpeechRecognizer alloc] initWithLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"en_US"]];
    speechRecognizer.delegate = self;
    [SFSpeechRecognizer requestAuthorization:^(SFSpeechRecognizerAuthorizationStatus status) {
        switch (status) {
            case SFSpeechRecognizerAuthorizationStatusAuthorized:
                NSLog(@"___FILTER___ Authorized");
                break;
            case SFSpeechRecognizerAuthorizationStatusDenied:
                NSLog(@"___FILTER___ Denied");
                break;
            case SFSpeechRecognizerAuthorizationStatusNotDetermined:
                NSLog(@"___FILTER___ Not Determined");
                break;
            case SFSpeechRecognizerAuthorizationStatusRestricted:
                NSLog(@"___FILTER___ Restricted");
                break;
            default:
                break;
        }
    }];
}

- (void)startListening {
    
    // Initialize the AVAudioEngine
    audioEngine = [[AVAudioEngine alloc] init];
    
    // Make sure there's not a recognition task already running
    if (recognitionTask) {
        [recognitionTask cancel];
        recognitionTask = nil;
    }
    
    // Starts an AVAudio Session
    NSError *error;
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    [audioSession setCategory:AVAudioSessionCategoryRecord error:&error];
    [audioSession setActive:YES withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:&error];
    
    NSLog(@"___FILTER___ RECORDING HAS STARTED???");
    
    // Starts a recognition process, in the block it logs the input or stops the audio
    // process if there's an error.
    recognitionRequest = [[SFSpeechAudioBufferRecognitionRequest alloc] init];
    AVAudioInputNode *inputNode = audioEngine.inputNode;
    recognitionRequest.shouldReportPartialResults = YES;
    recognitionTask = [speechRecognizer recognitionTaskWithRequest:recognitionRequest resultHandler:^(SFSpeechRecognitionResult * _Nullable result, NSError * _Nullable error) {
        BOOL isFinal = NO;
        if (result) {
            // Whatever you say in the microphone after pressing the button should be being logged
            // in the console.
            NSLog(@"___FILTER___ RESULT:%@",result.bestTranscription.formattedString);
            isFinal = !result.isFinal;
        }
        if (error) {
            [audioEngine stop];
            [inputNode removeTapOnBus:0];
            recognitionRequest = nil;
            recognitionTask = nil;
        }
    }];
    
    // Sets the recording format
    AVAudioFormat *recordingFormat = [inputNode outputFormatForBus:0];
    [inputNode installTapOnBus:0 bufferSize:1024 format:recordingFormat block:^(AVAudioPCMBuffer * _Nonnull buffer, AVAudioTime * _Nonnull when) {
        [recognitionRequest appendAudioPCMBuffer:buffer];
    }];
    
    // Starts the audio engine, i.e. it starts listening.
    [audioEngine prepare];
    [audioEngine startAndReturnError:&error];
    NSLog(@"___FILTER___ Say Something, I'm listening");
}

- (void) activateAudioStuff {
    if (audioEngine.isRunning) {
        [audioEngine stop];
        [recognitionRequest endAudio];
    } else {
        [self startListening];
    }
}

- (void)speechRecognizer:(SFSpeechRecognizer *)speechRecognizer availabilityDidChange:(BOOL)available {
//    NSLog(@"Availability:%d",available);
}

-(void) didBecomeActive
{
    if(m_pAppRunner != NULL)
    {
        m_pAppRunner->RequestLocationPermission();
    }
}

- (void)onPause
{
    m_pAppRunner->Pause();
    
// TODO: Not sure if we want to ignore this, EAGLContext* is _Nonnull
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnonnull"
    
    GLKView* glkView = (GLKView *)self.view;
    glkView.context = nil;
    
#pragma clang diagnostic pop
}

- (void)onResume
{
    GLKView* glkView = (GLKView *)self.view;
    glkView.context = [EAGLContext currentContext];

    m_pAppRunner->Resume();
    
    // Temporary line to force activation without implementing a specific button
    [self activateAudioStuff];
}

-(UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (void)viewWillLayoutSubviews
{
    if(m_pAppRunner == NULL)
    {
        AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
        
        self.pBackingView = [[[UIView alloc] initWithFrame:[self view].frame] autorelease];
        self.pBackingView.hidden = NO;
        self.pBackingView.backgroundColor = [UIColor clearColor];
        [[self view] addSubview:self.pBackingView];
        m_pAppRunner = new AppRunner(*self, [self view], *appDelegate.applicationConfiguration, *appDelegate.metricsService);
        if(appDelegate.launchUrl)
        {
            AppInterface::UrlData data;
            data.host = [appDelegate.launchUrl.host UTF8String];
            data.path = [appDelegate.launchUrl.path UTF8String];
            m_pAppRunner->HandleUrlOpen(data);
        }
    }
    [[self view] sendSubviewToBack:self.pBackingView];
    m_pAppRunner->NotifyViewLayoutChanged();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(m_pAppRunner == NULL)
    {
        return;
    }

    CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
    CFTimeInterval frameDuration = timeNow - m_previousTimestamp;
    
    const CFTimeInterval maxFrameInterval = 1.0f/self.preferredFramesPerSecond;
    
    frameDuration = Eegeo::Clamp<CFTimeInterval>(frameDuration, 0.0f, maxFrameInterval);
    
    m_pAppRunner->Update(static_cast<float>(frameDuration));

    const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
    Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));

    m_previousTimestamp = timeNow;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
    shouldReceiveTouch:(UITouch *)touch
{
    for (UIView *subview in [self view].subviews)
    {
// TODO: Way around this?
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-method-access"
        if ([subview respondsToSelector: @selector(consumesTouch:)])
        {
            if([subview consumesTouch: touch])
            {
                return NO;
            }
        }
#pragma clang diagnostic pop
    }
    return YES;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

-(void)willRotateToInterfaceOrientation: (UIInterfaceOrientation)orientation duration:(NSTimeInterval)duration
{

}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (m_pAppRunner == NULL) ? true : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}

- (BOOL)shouldAutorotate
{
    UIInterfaceOrientation interfaceOrientation = [[UIApplication sharedApplication] statusBarOrientation];

    return (m_pAppRunner == NULL) ? true : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}



@end
