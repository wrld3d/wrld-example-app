#pragma once

#import <UIKit/UIKit.h>

@protocol WRLDSearchResultModel;
@class WRLDSearchQuery;
@class WRLDSearchWidgetStyle;

@interface WRLDSearchResultTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *descriptionLabel;
@property (weak, nonatomic) IBOutlet UIImageView *iconImageView;

- (void) applyStyle: (WRLDSearchWidgetStyle*) style;
- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query;

@end
