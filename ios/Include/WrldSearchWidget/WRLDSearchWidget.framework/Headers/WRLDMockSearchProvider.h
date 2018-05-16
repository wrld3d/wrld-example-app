#pragma once

#import "WRLDSearchProvider.h"
#import "WRLDSuggestionProvider.h"

/*!
 An example WRLDSearchProvider and WRLDSuggestionProvider that returns a number of results after an interval.
 An NSInteger context passed to this provider will be used to specify a number of results to generate.
 Otherwise, the values set for the numReturnedSearchResults and numReturnedSuggestions will be used.
 */
@interface WRLDMockSearchProvider : NSObject <WRLDSearchProvider, WRLDSuggestionProvider>

/*!
 Create a new WRLDMockSearchProvider.
 @param searchDelayInSeconds amount of time to wait in seconds before completing a search query.
 @param suggestionDelayInSeconds amount of time to wait in seconds before completing a suggestion query.
 */
- (instancetype) initWithSearchDelayInSeconds: (CGFloat) searchDelayInSeconds suggestionDelayInSeconds:(CGFloat) suggestionDelayInSeconds;

/*!
 Number of search results to return if not specified in the WRLDSearchQuery context.
 */
@property (nonatomic) NSInteger numReturnedSearchResults;

/*!
 Number of suggestion (autocomplete) results to return if not specified in the WRLDSearchQuery context.
 */
@property (nonatomic) NSInteger numReturnedSuggestions;
@end

