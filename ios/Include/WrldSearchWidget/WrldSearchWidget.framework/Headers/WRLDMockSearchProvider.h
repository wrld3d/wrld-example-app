#pragma once

#import "WRLDSearchProvider.h"
#import "WRLDSuggestionProvider.h"

@interface WRLDMockSearchProvider : NSObject <WRLDSearchProvider, WRLDSuggestionProvider>
- (instancetype) initWithSearchDelayInSeconds: (CGFloat) searchDelayInSeconds suggestionDelayInSeconds:(CGFloat) suggestionDelayInSeconds;
@property (nonatomic) NSInteger numReturnedSearchResults;
@property (nonatomic) NSInteger numReturnedSuggestions;
@end

