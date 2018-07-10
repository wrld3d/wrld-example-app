#pragma once

#include <UIKit/UIKit.h>

@interface WRLDFadeableTableView : UITableView

- (void) createGradient;
- (void) updateScrollGradient: (BOOL) animate;
- (void) constrainFadeViewsTo: (UIView*) fadeConstrainer;

@end
