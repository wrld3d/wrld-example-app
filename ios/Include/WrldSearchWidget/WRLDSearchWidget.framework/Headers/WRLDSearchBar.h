#pragma once

#import <UIKit/UIKit.h>

@class WRLDControlStateColorMap;
@class WRLDSearchWidgetStyle;

@interface WRLDSearchBar : UISearchBar
-(void) setActive:(BOOL) isActive;
- (void) applyStyle: (WRLDSearchWidgetStyle *) style;
@end


