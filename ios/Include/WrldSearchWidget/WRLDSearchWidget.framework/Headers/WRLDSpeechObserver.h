#pragma once

#include <Foundation/Foundation.h>

/*!
 A method to be invoked when voice authorisation permissions change.
 @param authorized true if all permissions required to record voice input are granted.
 */
typedef void (^VoiceAuthorizedEvent) (BOOL authorized);

/*!
 An method when the speech capture state chages.
 */
typedef void (^VoiceEvent) (void);

/*!
 A method invoked when voice recording completes.
 @param transcript the best estimated match for the recorded audio input.
 */
typedef void (^VoiceRecordedEvent)(NSString* transcript);

/*!
 An method that is invoked frequently while audio is being recorded.
 @param sampleVolume a volume estimate for the audio sample.
 */
typedef void (^SampleTakenEvent)(CGFloat sampleVolume);

/*!
 Dispatches events related to obtaining voice input for the WRLDSearchWidget.
 */
@interface WRLDSpeechObserver : NSObject

/*!
 Add a method to be invoked when the permissions required for voice search change.
 @param event A method matching the VoiceAuthorizedEvent signature to invoke.
 */
- (void)addAuthorizationChangedEvent:(VoiceAuthorizedEvent)event;

/*!
 Stop invoking a method when the permissions required for voice search change.
 @param event A method to stop invoking.
 */
- (void)removeAuthorizationChangedEvent:(VoiceAuthorizedEvent)event;

/*!
 Add a method to be invoked when audio recording starts.
 The registered methods wait until permission to record is resolved before being invoked.
 If permission to record is denied the methods will not be called.
 @param event A method matching the VoiceEvent signature to invoke.
 */
- (void)addVoiceRecordStartedEvent:(VoiceEvent)event;

/*!
 Stop invoking a method when audio recording starts.
 @param event A method to stop invoking.
 */
- (void)removeVoiceRecordStartedEvent:(VoiceEvent)event;

/*!
 Add a method to be invoked when audio recording is completed and a transcript has been generated.
 Not invoked if the recording is cancelled.
 @param event A method matching the VoiceRecordedEvent signature to invoke.
 */
- (void)addVoiceRecordCompleteEvent:(VoiceRecordedEvent)event;

/*!
 Stop invoking a method when audio recording is completed.
 @param event A method to stop invoking.
 */
- (void)removeVoiceRecordCompleteEvent:(VoiceRecordedEvent)event;

/*!
 Add a method to be invoked when audio recording is cancelled.
 @param event A method matching the VoiceEvent signature to invoke.
 */
- (void)addVoiceRecordCancelledEvent:(VoiceEvent)event;

/*!
 Stop invoking a method when audio recording is cancelled.
 @param event A method to stop invoking.
 */
- (void)removeVoiceRecordCancelledEvent:(VoiceEvent)event;

/*!
 Add a method to be invoked when audio recording has taken a sample.
 These methods are called at frequent intervals during recording.
 @param event A method matching the SampleTakenEvent signature to invoke.
 */
- (void)addSampleTakenEvent:(SampleTakenEvent)event;

/*!
 Stop invoking a method when audio recording takes a sample.
 @param event A method to stop invoking.
 */
- (void)removeSampleTakenEvent:(SampleTakenEvent)event;

/*!
 Add a method to be invoked when the app denies the mircophone access permission.
 @param event A method matching the VoiceEvent signature to invoke.
 */
- (void)addMicrophoneAccessFailedEvent:(VoiceEvent)event;

/*!
 Stop invoking a method when the app denies the mircophone access permission.
 @param event A method to stop invoking.
 */
- (void)removeMicrophoneAccessFailedEvent:(VoiceEvent)event;

/*!
 Add a method to be invoked when the app denies the speech recognition permission.
 @param event A method matching the VoiceEvent signature to invoke.
 */
- (void)addSpeechRecognitionAccessFailedEvent:(VoiceEvent)event;

/*!
 Stop invoking a method when the app denies the speech recognition permission.
 @param event A method to stop invoking.
 */
- (void)removeSpeechRecognitionAccessFailedEvent:(VoiceEvent)event;

@end

