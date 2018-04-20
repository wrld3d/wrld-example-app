#pragma once

#include <Foundation/Foundation.h>

@protocol WRLDQueryFulfillerHandle;
@class WRLDSearchQuery;

typedef void (^QueryEvent) (WRLDSearchQuery * query);

@interface WRLDSearchQueryObserver : NSObject

- (void) addQueryStartingEvent :(QueryEvent) event;
- (void) removeQueryStartingEvent :(QueryEvent) event;

- (void) addQueryCompletedEvent :(QueryEvent) event;
- (void) removeQueryCompletedEvent :(QueryEvent) event;

- (void) addQueryCancelledEvent :(QueryEvent) event;
- (void) removeQueryCancelledEvent :(QueryEvent) event;

@end

