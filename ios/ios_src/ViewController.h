// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "AppRunner.h"

@interface UIViewController (SafeInsets)
- (UIEdgeInsets) safeInsets;
- (CGRect) largePopoverFrame;
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

-(CGRect) largePopoverFrameWithConstrainedWidth:(bool)shouldCapWidth
{
    UIEdgeInsets safeInsets = [self safeInsets];
    
    CGFloat sideMargin = 20;
    CGFloat bottomMargin = 30;
    CGFloat topMargin = 10;
    
    CGFloat boundsWidth = self.view.bounds.size.width - 2*sideMargin;

    const CGFloat boundsHeight = self.view.bounds.size.height - safeInsets.top - safeInsets.bottom - bottomMargin - topMargin;
    
    const bool useFullScreenSize = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
    
    const CGFloat boundsOccupyWidthMultiplier = useFullScreenSize ? 1.0f : (0.4f);
    const CGFloat boundsOccupyHeightMultiplier = useFullScreenSize ? 1.0f : (0.9);
    CGFloat mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    if(shouldCapWidth)
    {
        mainWindowWidth = MIN(boundsWidth * boundsOccupyWidthMultiplier, 348.f);
    }
    const CGFloat mainWindowHeight = boundsHeight * boundsOccupyHeightMultiplier;
    const CGFloat mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f) ;
    const CGFloat mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f)  ;
    
    return CGRectMake(mainWindowX + sideMargin,
                      mainWindowY + safeInsets.top + topMargin,
                      mainWindowWidth,
                      mainWindowHeight);
}

-(CGRect) largePopoverFrame
{
    return [self largePopoverFrameWithConstrainedWidth:false];
}

@end

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>
{
    CFTimeInterval m_previousTimestamp;
    AppRunner* m_pAppRunner;
}

@property (nonatomic, retain) UIView* pBackingView;

@end
