#pragma once

#include <Foundation/Foundation.h>

typedef void (^VoiceAuthorizedEvent) (BOOL authorized);

typedef void (^VoiceEvent) (void);

typedef void (^VoiceRecordedEvent)(NSString* transcript);

@interface WRLDSpeechObserver : NSObject

- (void)addAuthorizationChangedEvent:(VoiceAuthorizedEvent)event;

- (void)removeAuthorizationChangedEvent:(VoiceAuthorizedEvent)event;

- (void)addVoiceRecordStartedEvent:(VoiceEvent)event;

- (void)removeVoiceRecordStartedEvent:(VoiceEvent)event;

- (void)addVoiceRecordCompleteEvent:(VoiceRecordedEvent)event;

- (void)removeVoiceRecordCompleteEvent:(VoiceRecordedEvent)event;

- (void)addVoiceRecordCancelledEvent:(VoiceEvent)event;

- (void)removeVoiceRecordCancelledEvent:(VoiceEvent)event;

@end

