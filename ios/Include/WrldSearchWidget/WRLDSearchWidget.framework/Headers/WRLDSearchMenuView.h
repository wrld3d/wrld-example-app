#pragma once

#import <UIKit/UIKit.h>
#import "WRLDSearchWidgetTableViewContainer.h"

@interface WRLDSearchMenuView : WRLDSearchWidgetTableViewContainer

- (void) setTitleText: (NSString*) title;

- (void) resetScrollPositionIfMenuFitsOnScreen;

@end

