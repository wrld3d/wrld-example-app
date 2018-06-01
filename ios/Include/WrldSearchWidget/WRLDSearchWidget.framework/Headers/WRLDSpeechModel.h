#pragma once

#import <UIKit/UIKit.h>
#import <Speech/Speech.h>

@class WRLDSpeechCapture;
@class WRLDSpeechObserver;

API_AVAILABLE(ios(10.0))
@interface WRLDSpeechModel : NSObject <SFSpeechRecognizerDelegate>
@property (strong, nonatomic) AVAudioEngine* audioEngine;
@property (strong, nonatomic) NSTimer* speechTimeout;
@property (strong, nonatomic) SFSpeechAudioBufferRecognitionRequest *recognitionRequest;
@property (strong, nonatomic) SFSpeechRecognitionTask *recognitionTask;
@property (strong, nonatomic) SFSpeechRecognizer* speechRecognizer;
@property (strong, nonatomic) WRLDSpeechObserver* observer;

@property (nonatomic) BOOL isAuthorized;
@property (nonatomic) BOOL hasPartialResult;
@property (nonatomic) BOOL wasCancelled;
@property (nonatomic) BOOL isRecording;
@property (readonly, nonatomic) BOOL willStartRecordAfterAuthorizing;

-(void) authorize;
-(void) startRecording;
-(void) cancelRecording;
-(void) endRecording;

@end


