#pragma once

#import <UIKit/UIKit.h>
#import "WRLDFadeableView.h"

@interface WRLDNoSearchResultsView : WRLDFadeableView
@property (weak, nonatomic) IBOutlet UILabel* noResultsLabel;
@end

