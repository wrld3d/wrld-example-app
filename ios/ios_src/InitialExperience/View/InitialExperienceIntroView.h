// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InitialExperienceIntroViewIncludes.h"
#include "ViewWrap.h"
#include <string>

@class InitialExperienceIntroView;

class InitialExperienceIntroViewWrapper : public ViewWrap<InitialExperienceIntroView>
{
    using ViewWrap::ViewWrap;
};

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
@property (nonatomic, retain) UIView* pWelcomeImage;

@property (nonatomic, retain) UIView* pSettingsMenuDialogContainer;
@property (nonatomic, retain) UILabel* pSettingsMenuDialogTitle;
@property (nonatomic, retain) UITextView* pSettingsMenuDialogDescription;
@property (nonatomic, retain) UIView* pSettingsMenuDialogArrow;

@property (nonatomic, retain) UIView* pSearchMenuDialogContainer;
@property (nonatomic, retain) UILabel* pSearchMenuDialogTitle;
@property (nonatomic, retain) UITextView* pSearchMenuDialogDescription;
@property (nonatomic, retain) UIView* pSearchMenuDialogArrow;

@property (nonatomic, retain) UIView* pCompassDialogContainer;
@property (nonatomic, retain) UILabel* pCompassDialogTitle;
@property (nonatomic, retain) UITextView* pCompassDialogDescription;
@property (nonatomic, retain) UIView* pCompassDialogArrow;

@property (nonatomic, retain) UIView* pMapModeDialogContainer;
@property (nonatomic, retain) UILabel* pMapModeDialogTitle;
@property (nonatomic, retain) UITextView* pMapModeDialogDescription;
@property (nonatomic, retain) UIView* pMapModeDialogArrow;

@property (nonatomic, retain) UIView* pPinCreationDialogContainer;
@property (nonatomic, retain) UILabel* pPinCreationDialogTitle;
@property (nonatomic, retain) UITextView* pPinCreationDialogDescription;
@property (nonatomic, retain) UIView* pPinCreationDialogArrow;

@end
