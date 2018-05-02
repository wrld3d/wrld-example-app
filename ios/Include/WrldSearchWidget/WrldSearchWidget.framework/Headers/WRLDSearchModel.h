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
@property (nonatomic, readonly) BOOL isSearchQueryInFlight;

-(WRLDSearchProviderHandle *) addSearchProvider :(id<WRLDSearchProvider>) searchProvider;
-(void) removeSearchProvider :(WRLDSearchProviderHandle *) searchProviderHandle;

-(WRLDSuggestionProviderHandle *) addSuggestionProvider :(id<WRLDSuggestionProvider>) suggestionProvider;
-(void) removeSuggestionProvider :(WRLDSuggestionProviderHandle *) suggestionProviderHandle;

- (void)getSearchResultsForString:(NSString *) queryString;
- (void)getSuggestionsForString:(NSString *) queryString;

- (void)getSearchResultsForString:(NSString *) queryString withContext: (id<NSObject>) context;

- (void)cancelCurrentQuery;

- (WRLDSearchQuery *)getCurrentQuery;

- (BOOL)isCurrentQueryForSearch;

@end

