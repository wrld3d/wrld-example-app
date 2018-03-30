#pragma once

#include <Foundation/Foundation.h>

typedef void (^SearchbarFocusEvent) (void);

@interface WRLDSearchWidgetObserver : NSObject

- (void)addSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

- (void)removeSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

- (void)addSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

- (void)removeSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

@end
