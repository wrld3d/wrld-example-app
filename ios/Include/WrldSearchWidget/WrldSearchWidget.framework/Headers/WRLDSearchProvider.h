#pragma once

#import <UIKit/UIKit.h>

@class WRLDSearchRequest;

/*!
 A protocol defining the contract required to get results for a WRLDSearchWidgetModel.  Only search providers that return full results should implement this protocol.  Providers that return suggestions or autocomplete results should implement WRLDSuggestionProvider.
 */
@protocol WRLDSearchProvider

/*!
 NSString value displayed in the show more results view of WRLDSearchWidgetView.
 */
@property (nonatomic, readonly, copy) NSString *moreResultsName;

/*!
 This value will be used to decide which type of cell to use when displaying search results.
 See WRLDSearchResultTableViewCell for more details.
 */
@property (nonatomic, readonly, copy) NSString *cellIdentifier;

/*!
 Determines how much vertical space to assign a search result in the WRLDSearchWidgetView results table.
 */
@property (nonatomic, readonly) CGFloat cellHeight;

/*!
 Asks the provider to find results that match the query parameters.
 It is the providers responsibility to call WRLDSearchRequest didComplete with a set of results, or to cancel the request.
 @param query WRLDSearchRequest a request for results from the WRLDSearchModel.
 */
- (void) searchFor: (WRLDSearchRequest *) query;

@end
