#pragma once

#include <Foundation/Foundation.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchResultSelectedObserver;

/*!
 A method to be invoked when a search result item is selected from the WRLDSearchWidgetView.
 @param selectedResultModel a WRLDSearchResultModel representing the selected result.
 */
typedef void (^ResultSelectedEvent) (id<WRLDSearchResultModel> selectedResultModel);

/*!
 Registers methods to be invoked when search results are selected from the WRLDSearchWidgetView.
 */
@interface WRLDSearchResultSelectedObserver : NSObject

/*!
 Add a method to be invoked when search results are selected.
 @param event The method to be invoked.
 */
- (void) addResultSelectedEvent :(ResultSelectedEvent) event;

/*!
 Stop invoking a method when search results are selected.
 @param event The method to stop invoking.
 */
- (void) removeResultSelectedEvent :(ResultSelectedEvent) event;

@end


