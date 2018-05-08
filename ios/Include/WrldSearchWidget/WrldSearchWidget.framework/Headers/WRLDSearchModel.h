#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchProvider;
@protocol WRLDSuggestionProvider;
@class WRLDSearchProviderHandle;
@class WRLDSuggestionProviderHandle;
@class WRLDSearchQuery;
@class WRLDSearchQueryObserver;
@class WRLDSearchQueryOptions;

/*!
 The WRLDSearchModel dispatches WRLDSearchQueries to WRLDSearchProviders and WRLDSuggestionProviders.
 */
@interface WRLDSearchModel : NSObject

/*!
 @return WRLDSearchQueryObserver that dispatches events related to WRLDSearchProvider queries. The observers allows other objects to register to be notified when a search query is dispatched, completes or is cancelled.
 */
@property (readonly) WRLDSearchQueryObserver* searchObserver;

/*!
 @return A WRLDSearchQueryObserver that dispatches events related to WRLDSuggestionProvider queries. The observers allows other objects to register to be notified when a suggestion (autocomplete) query is dispatched, completes or is cancelled.
 */
@property (readonly) WRLDSearchQueryObserver* suggestionObserver;

/*!
 @return true if there is a Search or Suggestion query that has been dispatched but not cancelled or completed.
 */
@property (nonatomic, readonly) BOOL isSearchQueryInFlight;

/*!
 Add a search provider to the search model.
 @param searchProvider a WRLDSearchProvider to fulfill WRLDSearchRequests.
 @return a handle to uniquely idendify the WRLDSearchProvider within the model.
 */
- (WRLDSearchProviderHandle*) addSearchProvider: (id<WRLDSearchProvider>) searchProvider;

/*!
 Remove a search provider from the search model.
 @param searchProviderHandle a reference to a WRLDSearchProvider added to the WRLDSearchModel.
 */
- (void) removeSearchProvider: (WRLDSearchProviderHandle *) searchProviderHandle;

/*!
 Add a suggestion (autocomplete) provider to the search model.
 @param suggestionProvider a WRLDSuggestionProvider to fulfill WRLDSearchRequests for suggestions (autocomplete).
 @return a WRLDSuggestionProviderHandle to uniquely idendify the WRLDSearchProvider within the model.
 */
- (WRLDSuggestionProviderHandle*) addSuggestionProvider: (id<WRLDSuggestionProvider>) suggestionProvider;

/*!
 Remove a suggestion (autocomplete) provider from the search model.
 @param suggestionProviderHandle a reference to a WRLDSuggestionProvider added to the WRLDSearchModel.
 */
- (void) removeSuggestionProvider: (WRLDSuggestionProviderHandle*) suggestionProviderHandle;

/*!
 Sends search requests to all registered WRLDSearchProviders.
 @param queryString The string to be searched for.  Will be displayed in a WRLDSearchWidgetView using this model.
 */
- (void) getSearchResultsForString: (NSString*) queryString;

/*!
 Creates a new WRLDSearchQuery and dispatches the corresponding WRLDSearchRequests to all registered WRLDSuggestionProviders.
 @param queryString The string to be searched for.
 */
- (void) getSuggestionsForString: (NSString*) queryString;

/*!
 Sends search requests to all registered WRLDSearchProviders.
 @param queryString The string to be searched for.  Will be displayed in a WRLDSearchWidgetView using this model.
 @param options Additional options related to the search, including additonal context and whether to clear the previous results from WRLDSearchWidgetViews using this model.
 */
- (void) getSearchResultsForString: (NSString*) queryString withOptions: (WRLDSearchQueryOptions *) options;

/*!
 Cancels the current query if it is still in progress.  Completed WRLDSearchQueries cannot be cancelled.
 */
- (void) cancelCurrentQuery;

/*!
 Returns the most recent WRLDSearchQuery.  Queries for Suggestions replace queries for Search Results.
 @return the most recent query dispatched.
 */
- (WRLDSearchQuery*) getCurrentQuery;

/*!
 @return whether the most recent query for SearchResults or Suggesions (autocomplete).
 */
- (BOOL) isCurrentQueryForSearch;

@end

