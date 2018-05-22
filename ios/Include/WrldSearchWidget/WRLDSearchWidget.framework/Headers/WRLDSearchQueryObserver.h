#pragma once

#include <Foundation/Foundation.h>

@protocol WRLDQueryFulfillerHandle;
@class WRLDSearchQuery;

/*!
 A block that accepts a WRLDSearchQuery argument.
 */
typedef void (^QueryEvent) (WRLDSearchQuery * query);

@interface WRLDSearchQueryObserver : NSObject

/*!
 Adds a callback to be invoked when a query is dispatched.
 @param event A method that matches the QueryEvent signature.
 */
- (void) addQueryStartingEvent: (QueryEvent) event;

/*!
 Removes a callback invoked when a query is dispatched.
 @param event A method that matches the QueryEvent signature.
 */
- (void) removeQueryStartingEvent: (QueryEvent) event;

/*!
 Adds a callback to be invoked when a query is completed.
 A query is considered complete when all its providers invoke didComplete: withSuccess on the WRLDSearchRequests corresponding to the query.
 @param event A method that matches the QueryEvent signature.
 */
- (void) addQueryCompletedEvent: (QueryEvent) event;

/*!
 Removes a callback invoked when a query is completed.
 @param event A method that matches the QueryEvent signature.
 */
- (void) removeQueryCompletedEvent: (QueryEvent) event;

/*!
 Adds a callback to be invoked when a query is cancelled.
 @param event A method that matches the QueryEvent signature.
 */
- (void) addQueryCancelledEvent: (QueryEvent) event;

/*!
 Removes a callback invoked when a query is cancelled.
 @param event A method that matches the QueryEvent signature.
 */
- (void) removeQueryCancelledEvent: (QueryEvent) event;

@end

