#pragma once

#import <UIKit/UIKit.h>
#import <Speech/Speech.h>
#include <Foundation/Foundation.h>
#include "WRLDSpeechObserver.h"

@interface WRLDSpeechHandler : UIView <SFSpeechRecognizerDelegate>

    -(void) setPrompt:(NSString*)promptText;

    @property (readonly) BOOL isRecording;
    @property (readonly) BOOL isAuthorized;
    @property (readonly) NSString* promptText;

    @property (nonatomic, readonly) WRLDSpeechObserver * observer;

@end
