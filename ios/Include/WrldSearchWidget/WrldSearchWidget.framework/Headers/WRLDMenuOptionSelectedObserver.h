#pragma once

#include <Foundation/Foundation.h>

typedef void (^OptionSelectedEvent) (NSObject* selectedOptionContext);

@interface WRLDMenuOptionSelectedObserver : NSObject

- (void)addOptionSelectedEvent:(OptionSelectedEvent)event;

- (void)removeOptionSelectedEvent:(OptionSelectedEvent)event;

@end
