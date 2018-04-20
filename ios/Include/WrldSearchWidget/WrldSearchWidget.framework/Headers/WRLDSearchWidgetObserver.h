#pragma once

#include <Foundation/Foundation.h>

typedef void (^SearchbarFocusEvent) (void);

typedef void (^Event) (void);

@interface WRLDSearchWidgetObserver : NSObject

- (void)addSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

- (void)removeSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

- (void)addSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

- (void)removeSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

- (void)addSearchWidgetGainedFocusEvent:(Event)event;

- (void)removeSearchWidgetGainedFocusEvent:(Event)event;

- (void)addSearchWidgetResignedFocusEvent:(Event)event;

- (void)removeSearchWidgetResignedFocusEvent:(Event)event;

- (void)addSearchResultsReceivedEvent:(Event)event;

- (void)removeSearchResultsReceivedEvent:(Event)event;

- (void)addSearchResultsClearedEvent:(Event)event;

- (void)removeSearchResultsClearedEvent:(Event)event;

- (void)addSearchResultsShowingEvent:(Event)event;

- (void)removeSearchResultsShowingEvent:(Event)event;

- (void)addSearchResultsHiddenEvent:(Event)event;

- (void)removeSearchResultsHiddenEvent:(Event)event;

@end

