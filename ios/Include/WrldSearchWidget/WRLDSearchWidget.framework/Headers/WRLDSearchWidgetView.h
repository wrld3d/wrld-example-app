#pragma once

#import <UIKit/UIKit.h>

@class WRLDSearchModel;
@class WRLDSearchMenuModel;
@class WRLDSearchProviderHandle;
@class WRLDSuggestionProviderHandle;
@class WRLDSearchResultSelectedObserver;
@class WRLDMenuObserver;
@class WRLDSearchWidgetObserver;
@class WRLDSearchWidgetStyle;
@class WRLDSpeechCapture;
@class WRLDSearchResultContentObserver;

/*!
 Creates a search widget UIView.
 */
@interface WRLDSearchWidgetView : UIView <UISearchBarDelegate>

/*!
 @return WRLDSearchResultSelectedObserver that dispatches events when a search result is selected.
 */
@property (nonatomic, readonly) WRLDSearchResultSelectedObserver* searchSelectionObserver;

/*!
 @return WRLDSearchResultSelectedObserver that dispatches events when a suggestion is selected.
 */
@property (nonatomic, readonly) WRLDSearchResultSelectedObserver* suggestionSelectionObserver;


/*!
 @return WRLDSearchResultSelectedObserver that dispatches events when a search result is selected.
 */
@property (nonatomic, readonly) WRLDSearchResultContentObserver* searchResultContentObserver;

/*!
 @return WRLDSearchResultSelectedObserver that dispatches events when a suggestion is selected.
 */
@property (nonatomic, readonly) WRLDSearchResultContentObserver* suggestionContentObserver;

/*!
 See WRLDMenuObserver for a list of events.
 @return WRLDMenuObserver that dispatches events when a the search menu is interacted with.
 */
@property (nonatomic, readonly) WRLDMenuObserver* menuObserver;

/*!
 See WRLDSearchWidgetObserver for a list of events.
 @return WRLDSearchWidgetObserver that dispatches events when UI elements of the search widget change visiblity or gain or resign focus.
 */
@property (nonatomic, readonly) WRLDSearchWidgetObserver* observer;

/*!
 @return WRLDSearchWidgetStyle that can be used to customise the look of the Search Widget UI elements.
 */
@property (nonatomic, readonly) WRLDSearchWidgetStyle* style;

/*!
 @return indicates whether the UISearchBar in the search widget view has first responder status.
 */
@property (nonatomic, readonly) BOOL searchBarIsFirstResponder;

/*!
 @return true if the search menu is currently open.
 */
@property (nonatomic, readonly) BOOL isMenuOpen;

/*!
 @return indicates whether any of the results UIViews (search results, suggestions and no results) in the  search widget view are being displayed.
 */
@property (nonatomic, readonly) BOOL isResultsViewVisible;

/*!
 Indicates whether the search widget has any results to display.
 @return true if the last query was successful and returned more than zero results.
 */
@property (nonatomic, readonly) BOOL hasSearchResults;

/*!
 Indicates whether any of the search widget view elements are in focus.
 @return true if any result view is visible, the UISearchBar is being edited, or the menu is open.
 */
@property (nonatomic, readonly) BOOL hasFocus;

/*!
 A container for the search result and no results UIViews.
 The child views will not exceed the bounds of the container.
 */
@property (nonatomic, assign) UIView* resultsContainer;

/*!
 A container for the suggestions (autocomplete) UIView.
 The child view will not exceed the bounds of the container.
 */
@property (nonatomic, assign) UIView* suggestionsContainer;

/*!
 A container for the menu UIView.
 The child view will not exceed the bounds of the container.
 */
@property (nonatomic, assign) UIView* menuContainer;

/*!
 Boolean flag allowing the search results to be enabled or disabled
 */
@property (nonatomic) BOOL resultsVisible;

/*!
 Boolean flag allowing the suggestions to be enabled or disabled
 */
@property (nonatomic) BOOL suggestionsVisible;

/*!
 Boolean flag allowing the menu view to be enabled or disabled
 */
@property (nonatomic) BOOL menuVisible;

/*!
 @param searchModel WRLDSearchModel that should populate result views.
 */
- (void) useSearchModel: (WRLDSearchModel*) searchModel;

/*!
 @param menuModel WRLDSearchMenuModel that will populate the search menu.
 */
- (void) useMenuModel: (WRLDSearchMenuModel*) menuModel;

/*!
 Tells the search widget view to display search results from a provider.
 The provider handle must be obtained from the model passed to useSearchModel.
 @param searchProviderHandle WRLDSearchProviderHandle to a search provider.
 */
- (void) displaySearchProvider :(WRLDSearchProviderHandle*) searchProviderHandle;

/*!
 Stop displaying search results from a provider.
 @param searchProviderHandle WRLDSearchProviderHandle to a search provider.
 */
- (void) stopDisplayingSearchProvider :(WRLDSearchProviderHandle*) searchProviderHandle;

/*!
 Tells the WRLDSearchWidgetView to display suggestions from a provider.
 The provider handle must be obtained from the WRLDSearchModel passed to useSearchModel.
 @param suggestionProviderHandle WRLDSuggestionProviderHandle to a suggestion provider.
 */
- (void) displaySuggestionProvider :(WRLDSuggestionProviderHandle*) suggestionProviderHandle;

/*!
 Stop displaying search results from a provider.
 @param suggestionProviderHandle WRLDSuggestionProviderHandle to a suggestion provider.
 */
- (void) stopDisplayingSuggestionProvider :(WRLDSuggestionProviderHandle*) suggestionProviderHandle;

/*!
 Registers a UINib to be used with certain types of search providers.
 @param nib UINib containing a WRLDSearchResultTableViewCell.
 @param cellIdentifier NSString corresponding to an identifier provided by a search provider.
 */
- (void) registerNib: (UINib *) nib forUseWithResultsTableCellIdentifier: (NSString*) cellIdentifier;

/*!
 Clears the text in the UISearchbar and any search results currently being displayed.
 */
- (void) clearSearch;

/*!
 Tells the search widget view to bring up the appropriate view (search results, suggestions or no results) for the current set of results.
 */
- (void) showResultsView;

/*!
 Tells the search widget view to hide any currently displayed results views (search results, suggestions or no results).
 */
- (void) hideResultsView;

/*!
 Tells the search widget to collapse all results views to show the minimum number of results
 */
- (void) collapseResultsView;

/*!
 Minimises any open search results views (search results, suggestions or no results), stops editing the UISearchBar and closes the search menu.
 */
- (void) resignFocus;

/*!
 Opens the search menu.
 */
- (void) openMenu;

/*!
 Closes the search menu.
 */
- (void) closeMenu;

/*!
 Collapses all content in the search menu.
 */
- (void) collapseMenu;

/*!
 Expands the option at the specified index in the search menu.
 */
- (void) expandMenuOptionAt:(NSUInteger)index;

/*!
 Displays a button to allow use of the Speech Framework to populate the search.
 */
- (void) enableVoiceSearch:(WRLDSpeechCapture*)speechHandler;

/*!
 Turns off use of the Speech Framework.
 */
- (void) disableVoiceSearch;

/*!
 Sets the placeholder text of the UISearchBar when it contains no content.
 */
- (void) setSearchBarPlaceholder:(NSString*)placeholder;

/*!
 Updates layouts of children elements when the container is updated
 */
- (void) refreshLayout;

/*!
 Grants the Searchbar first responder status
 */
-(void) gainFocus;

@end
