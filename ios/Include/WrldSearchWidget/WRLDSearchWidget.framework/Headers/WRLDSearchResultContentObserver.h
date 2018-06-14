#pragma once

#include <Foundation/Foundation.h>

@class WRLDSearchResultTableViewCell;
@protocol WRLDSearchResultModel;

/*!
 A method to be invoked when a WRLDTableViewCell
 @param cell a WRLDSearchResultModel representing the selected result.
 */
typedef void (^WillPopulateCell) (WRLDSearchResultTableViewCell* cell);

/*!
 A method to be invoked after a cell is populated with content.
 @param cell a WRLDSearchResultModel representing the selected result.
 */
typedef void (^DidPopulateCell) (WRLDSearchResultTableViewCell* cell, id<WRLDSearchResultModel> content);

/*!
 Registers methods to be invoked when table view cells are populated with content
 */
@interface WRLDSearchResultContentObserver : NSObject

/*!
 Add a method to be invoked when a cell is about to be populated with new content
 The method will be invoked every time the cell is used or reused
 @param event The method to be invoked.
 */
- (void) addWillPopulateEvent :(WillPopulateCell) event;

/*!
 Stop invoking a method when a cell is about to be populated with new content
 @param event The method to stop invoking.
 */
- (void) removeWillPopulateEvent :(WillPopulateCell) event;

/*!
 Add a method to be invoked after a cell has been populated with new content
 @param event The method to be invoked.
 */
- (void) addDidPopulateEvent :(DidPopulateCell) event;

/*!
 Stop invoking a method after a cell has been populated with new content
 @param event The method to stop invoking.
 */
- (void) removeDidPopulateEvent :(DidPopulateCell) event;

@end


