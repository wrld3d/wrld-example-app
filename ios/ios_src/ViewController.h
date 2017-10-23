// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"

#import <Speech/Speech.h>

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate, SFSpeechRecognizerDelegate>
{
    CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
    
    SFSpeechRecognizer *speechRecognizer;
    SFSpeechAudioBufferRecognitionRequest *recognitionRequest;
    SFSpeechRecognitionTask *recognitionTask;
    AVAudioEngine *audioEngine;
}

@property (nonatomic, retain) UIView* pBackingView;

@end
