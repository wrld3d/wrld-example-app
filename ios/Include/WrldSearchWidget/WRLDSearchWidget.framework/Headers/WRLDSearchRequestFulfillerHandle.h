#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchResultSelectedObserver;

/*!
 A WRLDSearchRequestFulfillerHandle is a reference to an object that handles WRLDSearchRequests for a WRLDSearchModel.
 These will typically be WRLDSearchProviders or WRLDSuggestionProviders.
 */
@protocol WRLDSearchRequestFulfillerHandle

/*!
 @return A id that uniquely identifies the Fulfiller within the model.
 */
@property (readonly) NSInteger identifier;

/*!
 @return The height of cells corresponding to this fulfiller in the WRLDSearchWidgetView result views.
 */
@property (nonatomic, readonly) CGFloat cellHeight;

/*!
 @return The cellIdentifier to use for cells corresponding to this fulfiller in the WRLDSearchWidgetView result views. Cell identifies can be added to the WRLDSearchResultView using registerNib: forUseWithResultsTableCellIdentifier.
 */
@property (nonatomic, readonly) NSString* cellIdentifier;

/*!
 @return a string displayed in show more results cells of the WRLDSearchWidgetView results table.
 */
@property (nonatomic, readonly) NSString* moreResultsName;

/*!
 The WRLDSearchResultsObserver dispatches events when results corresponding to this Fulfiller are selected through the WRLDSearchWidgetView.
 @return selectionObserver An observer that manages blocks to call when a Fulfiller result is selected.
 */
@property (nonatomic, readonly) WRLDSearchResultSelectedObserver* selectionObserver;
@end

