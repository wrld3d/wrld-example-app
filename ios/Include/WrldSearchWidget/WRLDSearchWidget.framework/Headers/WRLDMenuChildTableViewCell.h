#pragma once

#import <UIKit/UIKit.h>

@class WRLDMenuTableSectionViewModel;
@class WRLDSearchWidgetStyle;

@interface WRLDMenuChildTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UIView *backgroundPanel;

@property (weak, nonatomic) IBOutlet UILabel *label;

@property (weak, nonatomic) IBOutlet UIImageView *icon;

@property (weak, nonatomic) IBOutlet UIView *separator;

@property (weak, nonatomic) IBOutlet UIView *shadowGradient;

- (void)populateWith:(WRLDMenuTableSectionViewModel *)viewModel
          childIndex:(NSUInteger)childIndex
               style:(WRLDSearchWidgetStyle *)style;

@end

