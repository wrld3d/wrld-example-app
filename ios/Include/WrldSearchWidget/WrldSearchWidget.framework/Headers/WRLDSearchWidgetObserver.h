#pragma once

#include <Foundation/Foundation.h>

typedef void (^FocusEvent) (void);

@interface WRLDSearchWidgetObserver : NSObject

- (void)addGainedFocusEvent:(FocusEvent)event;

- (void)removeGainedFocusEvent:(FocusEvent)event;

- (void)addResignedFocusEvent:(FocusEvent)event;

- (void)removeResignedFocusEvent:(FocusEvent)event;

@end
