#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchQuery;
@class WRLDSearchWidgetStyle;

/*!
 WRLDSearchResultTableViewCell represents a UITableViewCell that can be displayed by the WRLDSearchWidgetView.  When the content changes the cell will be updated by the WRLDSearchWidgetView by calling populateWith: WRLDSearchResultModel fromQuery: WRLDSearchQuery.
 */
@interface WRLDSearchResultTableViewCell : UITableViewCell

/*!
 @return the UILabel that corresponds to the title of the WRLDSearchResultModel.
 */
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;

/*!
 @return the UILabel that corresponds to the subtitle of the WRLDSearchResultModel.
 */
@property (weak, nonatomic) IBOutlet UILabel *descriptionLabel;

/*!
 @return the UILabel that corresponds to the iconKey of the WRLDSearchResultModel.
 */
@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;

/*!
 @return An NSDictionary corresponding to a UIFontDescriptor used to display text in the title UIView that does not match the WRLDSearchQuery querystring.
 */
@property (strong, nonatomic) NSDictionary *titleLabelRegularAttrs;

/*!
 @return An NSDictionary corresponding to a UIFontDescriptor used to display text in the title UIView that matches the WRLDSearchQuery querystring.
 */
@property (strong, nonatomic) NSDictionary *titleLabelHighlightAttrs;

/*!
 @return An NSDictionary corresponding to a UIFontDescriptor used to display text in the description UIView that does not match the WRLDSearchQuery querystring.
 */
@property (strong, nonatomic) NSDictionary *descriptionLabelRegularAttrs;

/*!
 @return An NSDictionary corresponding to a UIFontDescriptor used to display text in the description UIView that matches the WRLDSearchQuery querystring.
 */
@property (strong, nonatomic) NSDictionary *descriptionLabelHighlightAttrs;

/*!
 Called on initialisation of the cell and before populate with to adjust the cell view.
 @param style the WRLDSearchWidgetStyle of the WRLDSearchWidgetView.
 */
- (void) applyStyle: (WRLDSearchWidgetStyle*) style;

/*!
 Called when the search widget view is about to display a result in the cell.
 Beware of cached content from old results - clear any data you don't want to be visible each time the cell is populated.
 @param searchResult WRLDSearchResultModel of the result about to be displayed.
 @param query WRLDSearchQuery that returned the result.
 */
- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query;

@end
