#pragma once

#import <UIKit/UIKit.h>
#import <Speech/Speech.h>
#include <Foundation/Foundation.h>
#include "WRLDSpeechObserver.h"

/*!
 WRLDSpeechCapture is a UIView element that is displayed when capturing voice input to use with the WRLDSearchWidget.
 */
@interface WRLDSpeechCapture : UIView

/*!
 Attempts to get approval from the device to record voice.
 */
-(void) authorize;

/*!
 Attempts to get start voice recording.  If it does not have permission, attempts to authorize. If permission has already been denied,
 does not start recording.
 */
-(void) startRecording;

/*!
 Cancels the current recording.
 */
-(void) cancelRecording;

/*!
 Set the text message displayed when recording voice input.
 */
-(void) setPrompt:(NSString*) promptText;

/*!
 @return true if currently recording voice input.
 */
@property (readonly) BOOL isRecording;

/*!
 @return true if permission to record voice input has been allowed.
 */
@property (readonly) BOOL isAuthorized;

/*!
 @return the text to display on screen when recording voice input.
 */
@property (readonly) NSString* promptText;

/*!
 @return an observer that dispatches events when using voice input.
 */
@property (nonatomic, readonly) WRLDSpeechObserver * observer;

@end
