#pragma once

#include "WRLDSearchQuery.h"
#include "WRLDSearchTypes.h"
#include "WRLDSearchTypes(Private).h"

@class WRLDSearchQueryObserver;
@class WRLDSearchRequest;
@protocol WRLDSearchRequestFulfillerHandle;

@interface WRLDSearchQuery (Private)

- (instancetype) initWithQueryString: (NSString*) queryString
                       queryObserver: (WRLDSearchQueryObserver *) queryObserver;

- (instancetype) initWithQueryString: (NSString*) queryString
                             options: (WRLDSearchQueryOptions *) options
                       queryObserver: (WRLDSearchQueryObserver *) queryObserver;

@property (nonatomic, readonly) BOOL willClearPreviousResultsOnStart;

- (void) dispatchRequestsToSearchProviders: (WRLDSearchRequestFulfillerCollection *) providerHandles;
- (void) dispatchRequestsToSuggestionProviders: (WRLDSearchRequestFulfillerCollection *) providerHandles;

- (void) addResults: (WRLDSearchResultsCollection *) results fromFulfiller: (id<WRLDSearchRequestFulfillerHandle>) fulfillerHandle withSuccess: (BOOL) success;

- (void) cancelRequest: (WRLDSearchRequest *) cancelledRequest;
@end


