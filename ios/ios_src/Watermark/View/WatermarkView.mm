// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WatermarkViewInterop.h"
#include "MathFunc.h"
#include "ImageHelpers.h"
#include "App.h"

@implementation WatermarkView

- (ExampleApp::Watermark::View::WatermarkViewInterop *)getInterop
{
    return m_pInterop;
}

- (id) initWithDimensions:(float)width :(float)height :(float)pixelScale :(const std::string&) googleAnalyticsReferrerToken
{
    if(self = [super init])
    {
        [self setAlpha:0.8f];

        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_googleAnalyticsReferrerToken = googleAnalyticsReferrerToken;

        m_pInterop = new ExampleApp::Watermark::View::WatermarkViewInterop(self);
        [self addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"eegeo_logo") forState:UIControlStateNormal];
        
        m_width = 140 * m_pixelScale;
        m_height = 52 * m_pixelScale;
        
        if(App::IsDeviceSmall())
        {
            m_yPosActive = (20 * m_pixelScale);
            m_yPosInactive = (-m_height);
            
            self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_width * 0.5f)),
                                    m_yPosInactive,
                                    m_width,
                                    m_height);
        }
        else
        {
            m_yPosActive = m_screenHeight - m_height - (8 * m_pixelScale);
            m_yPosInactive = (m_screenWidth + m_height);
            
            self.frame = CGRectMake(((m_screenWidth) - (m_width) - (8 * m_pixelScale)),
                                    m_yPosInactive,
                                    m_width,
                                    m_height);
        }
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
    }

    return self;
}

- (void)dealloc
{
    delete m_pInterop;
    [m_pController release];
    [super dealloc];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) onClick:(UIButton *)sender
{
    NSString* appName =  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
    NSString* alertTitle = @"Maps by eeGeo";
    NSString* alertMessage = [NSString stringWithFormat: @"The %@ app is open source. It's built using the eeGeo maps SDK, a cross platform API for building engaging, customizable apps.", appName];
    NSString* cancelMessage = @"Later";
    NSString* goToSiteMessage = @"Find Out More";
    
    if([UIAlertController class])
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                       message:alertMessage
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* openSiteAction = [UIAlertAction actionWithTitle:goToSiteMessage
                                                                 style:UIAlertActionStyleDefault
                                                               handler:^(UIAlertAction * action) { [self openEegeoWebsite]; }];
        
        UIAlertAction* cancelAction = [UIAlertAction actionWithTitle:cancelMessage
                                                               style:UIAlertActionStyleCancel
                                                             handler:^(UIAlertAction * action) {}];
        
        [alert addAction:openSiteAction];
        [alert addAction:cancelAction];
        [m_pController presentViewController:alert animated:YES completion:nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:cancelMessage
                                              otherButtonTitles:goToSiteMessage, nil];
        
        
        
        [alert show];
        [alert release];
    }
    
    m_pInterop->OnSelected();
}

- (void) setFullyOnScreen
{
    if(self.frame.origin.y == m_yPosActive)
    {
        return;
    }
    
    [self animateToY:m_yPosActive];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.y == m_yPosInactive)
    {
        return;
    }
    
    [self animateToY:m_yPosInactive];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = false;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
}

- (void) animateToY:(float)y
{
    CGRect f = self.frame;
    f.origin.y = y;
    
    if(y != m_yPosInactive)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.frame = f;
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (y == m_yPosInactive);
     }
     ];
}

- (void) openEegeoWebsite
{
    NSString* urlString = [NSString stringWithFormat
                           :@"http://eegeo.com/findoutmore?utm_source=%@&utm_medium=referral&utm_campaign=eegeo",
                           [NSString stringWithUTF8String:m_googleAnalyticsReferrerToken.c_str()]
                           ];
    
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlString]];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1)
    {
        [self openEegeoWebsite];
    }
}

@end

