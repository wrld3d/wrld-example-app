#pragma once

#import <UIKit/UIKit.h>

@class WRLDSearchWidgetResultSetViewModel;
@class WRLDSearchWidgetStyle;

@interface WRLDMoreResultsTableViewCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (weak, nonatomic) IBOutlet UIImageView *icon;
- (void) applyStyle: (WRLDSearchWidgetStyle*) style;
- (void) populateWith: (NSString*) text icon: (UIImage *) icon;
@end
