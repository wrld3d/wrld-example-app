// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "UIView+TouchExclusivity.h"

@implementation UIView (TouchExclusivity)

- (void) setTouchExclusivity:(UIView *)view
{
    for (UIView *subView in [view subviews])
    {
        if ([subView subviews] != nil)
        {
            [self setTouchExclusivity: subView];
        }
        
        subView.exclusiveTouch = YES;
    }
}

@end