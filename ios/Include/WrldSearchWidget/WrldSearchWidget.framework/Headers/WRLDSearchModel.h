#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchProvider;
@protocol WRLDSuggestionProvider;
@protocol WRLDFinishedSearchDelegate;
@class WRLDSearchProviderHandle;
@class WRLDSuggestionProviderHandle;
@class WRLDSearchQuery;
@class WRLDSearchQueryObserver;

@interface WRLDSearchModel : NSObject
@property (readonly) WRLDSearchQueryObserver * searchObserver;
@property (readonly) WRLDSearchQueryObserver * suggestionObserver;

-(WRLDSearchProviderHandle *) addSearchProvider :(id<WRLDSearchProvider>) searchProvider;
-(void) removeSearchProvider :(WRLDSearchProviderHandle *) searchProviderHandle;

-(WRLDSuggestionProviderHandle *) addSuggestionProvider :(id<WRLDSuggestionProvider>) suggestionProvider;
-(void) removeSuggestionProvider :(WRLDSuggestionProviderHandle *) suggestionProviderHandle;

-(WRLDSearchQuery *) getSearchResultsForString:(NSString *) queryString;
-(WRLDSearchQuery *) getSuggestionsForString:(NSString *) queryString;
@end

