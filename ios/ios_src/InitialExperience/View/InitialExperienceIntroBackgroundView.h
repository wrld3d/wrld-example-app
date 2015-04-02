// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InitialExperienceIntroViewIncludes.h"
#include <string>

@class InitialExperienceIntroBackgroundView;

@interface InitialExperienceIntroBackgroundView : UIView <UIGestureRecognizerDelegate>
{
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_animationTimeSeconds;
    CGFloat m_screenWidth;
    CGFloat m_screenHeight;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) show;

- (void) dismiss;

@property (nonatomic, retain) UIView* pBackground;

@end
