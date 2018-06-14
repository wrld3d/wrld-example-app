#pragma once

#import <Foundation/Foundation.h>

@class WRLDSearchRequest;

@class WRLDSearchQuery;

/*!
 A protocol defining the contract required to get suggestions for a WRLDSearchWidgetModel. Only search providers that return suggestions for autocomplete should implement this protocol.  Providers that return full search results should implement WRLDSearchProvider.
 */
@protocol WRLDSuggestionProvider

/*!
 Asks the provider to find suggestions that match the query parameters.
 It is the providers responsibility to call WRLDSearchRequest didComplete with a set of results, or to cancel the request.
 @param query WRLDSearchRequest a request for results from the WRLDSearchModel.
 */
- (void) getSuggestions: (WRLDSearchRequest *) query;
@end
