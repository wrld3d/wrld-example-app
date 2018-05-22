#pragma once

#import <UIKit/UIKit.h>

@class WRLDMenuTableSectionViewModel;
@class WRLDSearchWidgetStyle;

@interface WRLDMenuGroupTitleTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *label;

@property (weak, nonatomic) IBOutlet UIView *groupSeparator;

@property (weak, nonatomic) IBOutlet UIView *separator;

- (void)populateWith:(WRLDMenuTableSectionViewModel *)viewModel
 isFirstTableSection:(bool)isFirstTableSection
               style:(WRLDSearchWidgetStyle *)style;

@end
