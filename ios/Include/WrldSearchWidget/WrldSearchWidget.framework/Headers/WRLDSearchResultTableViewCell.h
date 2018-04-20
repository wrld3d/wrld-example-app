#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchQuery;
@class WRLDSearchWidgetStyle;

@interface WRLDSearchResultTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *descriptionLabel;
@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;

@property (strong, nonatomic) NSDictionary *titleLabelRegularAttrs;
@property (strong, nonatomic) NSDictionary *titleLabelBoldAttrs;
@property (strong, nonatomic) NSDictionary *descriptionLabelRegularAttrs;
@property (strong, nonatomic) NSDictionary *descriptionLabelBoldAttrs;

- (void) applyStyle: (WRLDSearchWidgetStyle*) style;
- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query;

@end
