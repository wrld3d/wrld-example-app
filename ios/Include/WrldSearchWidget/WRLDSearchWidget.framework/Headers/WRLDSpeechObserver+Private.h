#pragma once

#include "WRLDSpeechObserver.h"

@interface WRLDSpeechObserver (Private)

- (void)authorizationChanged:(BOOL)authorized;

- (void)speechRecordingStarted;

- (void)speechRecordingCancelled;

- (void)speechRecordingCompleted:(NSString*)transcript;

- (void)sampleTaken:(CGFloat) sampleVolume;

- (void)microphoneAccessFailed;

- (void)speechRecognitionAccessFailed;

@end

