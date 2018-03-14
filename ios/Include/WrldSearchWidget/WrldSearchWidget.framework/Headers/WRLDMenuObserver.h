#pragma once

#include <Foundation/Foundation.h>

typedef void (^OptionSelectedEvent) (NSObject* selectedOptionContext);

typedef void (^OptionExpandedEvent) (NSObject* expandedOptionContext, BOOL fromInteraction);

typedef void (^OptionCollapsedEvent) (NSObject* collapsedOptionContext, BOOL fromInteraction);

@interface WRLDMenuObserver : NSObject

- (void)addOptionSelectedEvent:(OptionSelectedEvent)event;

- (void)removeOptionSelectedEvent:(OptionSelectedEvent)event;

- (void)addOptionExpandedEvent:(OptionExpandedEvent)event;

- (void)removeOptionExpandedEvent:(OptionExpandedEvent)event;

- (void)addOptionCollapsedEvent:(OptionCollapsedEvent)event;

- (void)removeOptionCollapsedEvent:(OptionCollapsedEvent)event;

@end
