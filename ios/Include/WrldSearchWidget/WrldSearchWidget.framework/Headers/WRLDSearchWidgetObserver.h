#pragma once

#include <Foundation/Foundation.h>

/*!
 A method to be invoked when the Searchbar within the search widget view becomes the first responder.
 */
typedef void (^SearchbarFocusEvent) (void);

/*!
 A method to be invoked when the text content of the Searchbar within the search widget view changes.
 @param newString the new content of the Searchbar.
 */
typedef void (^SearchbarTextChangedEvent) (NSString * newString);

/*!
 A void method to be called whenever events related to the search widget view occur.
 */
typedef void (^Event) (void);

/*!
 Observes the search widget view and invokes registered methods when events occur.
 */
@interface WRLDSearchWidgetObserver : NSObject

/*!
 Add a method to be invoked when the Searchbar within the search widget view becomes first responder.
 @param event a method matching the SearchBarFocusEvent signature to invoke.
 */
- (void)addSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

/*!
 Stops invoking a method when the Searchbar within the search widget view becomes first responder.
 @param event the method to stop invoking.
 */
- (void)removeSearchbarGainedFocusEvent:(SearchbarFocusEvent)event;

/*!
 Add a method to be invoked when the Searchbar within the search widget view resigns as first responder.
 @param event a method matching the SearchBarFocusEvent signature to invoke.
 */
- (void)addSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

/*!
 Stops invoking a method when the Searchbar within the search widget view resigns as first responder.
 @param event the method to stop invoking.
 */
- (void)removeSearchbarResignedFocusEvent:(SearchbarFocusEvent)event;

/*!
 Add a method to be invoked when the text of the Searchbar within the search widget view changes.
 @param event a method matching the SearchBarFocusEvent signature to invoke.
 */
- (void)addSearchbarTextChangedEvent:(SearchbarTextChangedEvent)event;

/*!
 Stops invoking a method when the text of the Searchbar within the search widget view changes.
 @param event the method to stop invoking.
 */
- (void)removeSearchbarTextChangedEvent:(SearchbarTextChangedEvent)event;

/*!
 Add a method to be invoked when the search widget view gains focus.
 The widget is considered to have focus when the menu is open, or if the suggestions, search results or no results views are visible, or if the Searchbar has first responder status.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchWidgetGainedFocusEvent:(Event)event;

/*!
 Stops invoking a method when the search widget view gains focus.
 @param event the method to stop invoking.
 */
- (void)removeSearchWidgetGainedFocusEvent:(Event)event;

/*!
 Add a method to be invoked when the search widget view resigns focus.
 The widget is considered to have resigned focus when the menu is closed, none of the suggestions, search results or no results views are visible, and the Searchbar is not the first responder.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchWidgetResignedFocusEvent:(Event)event;

/*!
 Stops invoking a method when the search widget view resigns focus.
 @param event the method to stop invoking.
 */
- (void)removeSearchWidgetResignedFocusEvent:(Event)event;

/*!
 Add a method to be invoked when the search widget view receives SearchResults to display.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchResultsReceivedEvent:(Event)event;

/*!
 Stops invoking a method when the search widget view receives SearchResults to display.
 @param event the method to stop invoking.
 */
- (void)removeSearchResultsReceivedEvent:(Event)event;

/*!
 Add a method to be invoked when the search widget view clears the current results being displayed.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchResultsClearedEvent:(Event)event;

/*!
 Stops invoking a method when the search widget view clears the current results being displayed.
 @param event the method to stop invoking.
 */
- (void)removeSearchResultsClearedEvent:(Event)event;

/*!
 Add a method to be invoked when the search widget view starts showing one of its results screens.
 The results screens are the suggestions view, the search results view and the no results view.
 This method will not be invoked if one screen is replaced with another.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchResultsShowingEvent:(Event) event;

/*!
 Stops invoking a method when the search widget view starts showing one of its results screens.
 The results screens are the suggestions view, the search results view and the no results view.
 @param event the method to stop invoking.
 */
- (void)removeSearchResultsShowingEvent:(Event)event;

/*!
 Add a method to be invoked when the search widget view no longer shows a results screen.
 The results screens are the suggestions view, the search results view and the no results view.
 Methods will not be invoked if one screen is replaced with another - they are called when none of the screens are visible.
 @param event a method matching the Event signature to invoke.
 */
- (void)addSearchResultsHiddenEvent:(Event)event;

/*!
 Stops invoking a method when the search widget view no longer shows a results screen.
 @param event the method to stop invoking.
 */
- (void)removeSearchResultsHiddenEvent:(Event)event;

@end

