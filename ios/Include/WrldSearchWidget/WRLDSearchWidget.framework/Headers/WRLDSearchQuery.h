#pragma once
#import <Foundation/Foundation.h>

#import "WRLDSearchTypes.h"

@protocol WRLDSearchResultModel;
@protocol WRLDQueryFulfillerHandle;

/*!
 A search query performed by the WRLDSearchModel.  A query can span multiple providers.
*/
@interface WRLDSearchQuery : NSObject


/*!
The states a query can be in.
*/
typedef NS_ENUM(NSInteger, WRLDSearchQueryProgressStatus) {
    WRLDSearchQueryProgressStatusNotStarted,
    WRLDSearchQueryProgressStatusInFlight,
    WRLDSearchQueryProgressStatusCancelled,
    WRLDSearchQueryProgressStatusCompleted
};

/*!
The text string associated with the query.  This will be displayed in the WRLDSearchWidgetView's SearchView.
*/
@property (copy, readonly) NSString* queryString;

/*!
 The progress status of the query.
 */
@property (readonly) WRLDSearchQueryProgressStatus progress;

/*!
 @return true if the query has successfully completed with all providers.
 */
@property (readonly) BOOL hasSucceeded;

/*!
 @return true if the query has been comleted by all providers or has been cancelled.
 */
@property (readonly) BOOL hasCompleted;

/*!
 Additional search information that can be used by SearchResultsFulfillers.
 */
@property (readonly) id<NSObject> queryContext;

/*!
 Returns a collection of results that corresponds to a particular WRLDSearchProvider or WRLDSuggestionProvider.
 @param fulfillerHandleId an ID that uniquely identifies a WRLDSearchProvider or WLRDSuggestionProvider within a WRLDSearchModel.
 The id can be obtained from the WRLDSearchResuestFulfillerHandle returned when the providers are added to the WRLDSearchModel.
 @return NSArray of WRLDSearchResult objects
 */
- (WRLDSearchResultsCollection *) getResultsForFulfiller: (NSInteger) fulfillerHandleId;

/*!
 Cancels the query.  No results will be accepted from providers.
 */
- (void) cancel;
@end

/*!
 Options used when a query is performed by a model.
 */
@interface WRLDSearchQueryOptions : NSObject

/*!
 Additional context passed to the query fulfillers.
 Default is nil when there is no additional context.
 @return Context relevant to the query.
 */
@property (strong, readonly) NSObject *context;

/*!
 If the query is displayed in a WRLDSearchProviderView, this boolean indicates whether the previous results.
 are cleared from the view when the query is sent to fulfillers.  The previous query's results will always be removed when
 a new query completes.
 Default is YES - previous query results will be cleared immediatley when the new query is dispatched.
 @return shouldClearPreviousResultsWhenStarted BOOL whether to clear the previous results when the query is dispatched to providers.
 */
@property (readonly) BOOL shouldClearPreviousResultsWhenStarted;

/*!
 Creates options to be used with a query.
 @param context Context relevant to the query.
 @param shouldClear Whether to clear any existing results upon dispatch.
 @return Options corresponding to the query.
 */
+(instancetype) withContext: (NSObject *) context shouldClearPreviousResults: (BOOL) shouldClear;

/*!
 Creates options to be used with a query.
 @param context Context relevant to the query.
 @return Options corresponding to the query.
 */
+(instancetype) withContext: (NSObject *) context;

/*!
 Creates options to be used with a query.
 @param shouldClear Whether to clear any existing results upon dispatch.
 @return Options corresponding to the query.
 */
+(instancetype) withClearPreviousResults: (BOOL) shouldClear;

@end
