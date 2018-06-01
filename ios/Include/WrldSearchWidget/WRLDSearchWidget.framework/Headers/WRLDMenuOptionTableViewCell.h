#pragma once

#import <UIKit/UIKit.h>

@class WRLDMenuTableSectionViewModel;
@class WRLDSearchWidgetStyle;

@interface WRLDMenuOptionTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *label;

@property (weak, nonatomic) IBOutlet UIImageView *expander;

@property (weak, nonatomic) IBOutlet UIView *groupSeparator;

@property (weak, nonatomic) IBOutlet UIView *separator;

- (void)populateWith:(WRLDMenuTableSectionViewModel *)viewModel
 isFirstTableSection:(bool)isFirstTableSection
        expanderIcon:(UIImage *)expanderIcon
     highlightedIcon:(UIImage *)highlightedIcon
               style:(WRLDSearchWidgetStyle *)style;

@end
