// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InitialExperienceIntroViewIncludes.h"
#include <string>

@class InitialExperienceIntroView;

@interface InitialExperienceIntroView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::InitialExperience::View::InitialExperienceIntroViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_animationTimeSeconds;
    CGFloat m_screenWidth;
    CGFloat m_screenHeight;
    BOOL m_awaitingInput;
}

- (id) initView: (InitialExperienceIntroBackgroundView*)pBackground;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) show;

- (void) dismiss;

- (ExampleApp::InitialExperience::View::InitialExperienceIntroViewInterop*) getInterop;

@property (nonatomic, retain) UIView* pBackgroundContainer;

@property (nonatomic, retain) UIView* pBannerBarContainer;
@property (nonatomic, retain) UIView* pBannerBarOutline;
@property (nonatomic, retain) UIView* pBannerBarBackground;
@property (nonatomic, retain) UILabel* pWelcomeText;

@property (nonatomic, retain) UIView* pSearchMenuDialogContainer;
@property (nonatomic, retain) UIView* pSearchMenuDialogContent;
@property (nonatomic, retain) UIView* pSearchMenuDialogIcon;
@property (nonatomic, retain) UILabel* pSearchMenuDialogTitle;
@property (nonatomic, retain) UITextView* pSearchMenuDialogDescription;
@property (nonatomic, retain) UIView* pSearchMenuDialogArrow;
@property (nonatomic, retain) UIView* pSearchMenuDialogArrowOutline;

@property (nonatomic, retain) UIView* pCompassDialogContainer;
@property (nonatomic, retain) UIView* pCompassDialogContent;
@property (nonatomic, retain) UIView* pCompassDialogIcon;
@property (nonatomic, retain) UILabel* pCompassDialogTitle;
@property (nonatomic, retain) UITextView* pCompassDialogDescription;
@property (nonatomic, retain) UIView* pCompassDialogArrow;
@property (nonatomic, retain) UIView* pCompassDialogArrowOutline;

@end
