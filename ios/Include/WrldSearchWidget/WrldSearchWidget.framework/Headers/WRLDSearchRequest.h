#pragma once
#import <Foundation/Foundation.h>

#import "WRLDSearchTypes.h"

@protocol WRLDSearchResultsCollection;
@class WRLDSearchQuery;

/*!
 A WRLDSearchRequest corresponds to a WRLDSearchQuery for a specific WRLDSearchProvider or WRLDSuggestionProvider.
 WRLDSearchProviders and WRLDSuggestionProviders do not deal with queries directly - they each fulfil their specific requests.
 */
@interface WRLDSearchRequest : NSObject

/*!
 @return the search string of the corresponding query.
 */
@property (copy, readonly) NSString* queryString;

/*!
 @return additional context related to the corresponding query.
 */
@property (copy, readonly) id<NSObject> queryContext;

/*!
 @return true if the request has completed.
 */
@property (readonly) BOOL hasCompleted;

/*!
 Cancels the request.  A cancelled request cancels the query.  It is up to the fulfiller to call either this or didComplete: withResults to allow the query to complete.
 */
-(void) cancel;

/*!
 This method is completes the fulfillers part of the request.  It is up to the fulfiller to call either this or cancel to allow the query to complete.
 @param success Whether the fulfiller successfully handed the request.
 @param results The results from the fulfiller for the request.
 */
-(void) didComplete:(BOOL) success withResults:(WRLDSearchResultsCollection *) results;

@end

