#pragma once

#include <Foundation/Foundation.h>

typedef void (^OpenedEvent) (BOOL fromInteraction);

typedef void (^ClosedEvent) (BOOL fromInteraction);

typedef void (^OptionSelectedEvent) (NSObject* selectedOptionContext);

typedef void (^OptionExpandedEvent) (NSObject* expandedOptionContext, BOOL fromInteraction);

typedef void (^OptionCollapsedEvent) (NSObject* collapsedOptionContext, BOOL fromInteraction);

@interface WRLDMenuObserver : NSObject

- (void)addOpenedEvent:(OpenedEvent)event;

- (void)removeOpenedEvent:(OpenedEvent)event;

- (void)addClosedEvent:(ClosedEvent)event;

- (void)removeClosedEvent:(ClosedEvent)event;

- (void)addOptionSelectedEvent:(OptionSelectedEvent)event;

- (void)removeOptionSelectedEvent:(OptionSelectedEvent)event;

- (void)addOptionExpandedEvent:(OptionExpandedEvent)event;

- (void)removeOptionExpandedEvent:(OptionExpandedEvent)event;

- (void)addOptionCollapsedEvent:(OptionCollapsedEvent)event;

- (void)removeOptionCollapsedEvent:(OptionCollapsedEvent)event;

@end
