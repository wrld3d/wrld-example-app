// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"

@interface UIViewController (SafeInsets)
- (UIEdgeInsets ) safeInsets;
@end

@implementation UIViewController (SafeInsets)
- (UIEdgeInsets ) safeInsets
{
    if (@available(iOS 11, *)) {
        return self.view.safeAreaInsets;
    }
    else {
        return UIEdgeInsetsMake(self.topLayoutGuide.length, 0, self.bottomLayoutGuide.length, 0);
    }
}
@end

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>
{
    CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
}

@property (nonatomic, retain) UIView* pBackingView;

@end
