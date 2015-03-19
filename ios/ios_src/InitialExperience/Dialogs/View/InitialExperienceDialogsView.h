// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InitialExperienceDialogsViewIncludes.h"
#include "InitialExperienceDialogType.h"
#include <string>

@class InitialExperienceDialogsView;

@interface InitialExperienceDialogsView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_animationTimeSeconds;
    BOOL m_visible;
    BOOL m_modalBackgroundActive;
    CGFloat m_screenWidth;
    CGFloat m_screenHeight;
    CGFloat m_dialogContainerWidth;
    CGFloat m_dialogContainerHeight;
    CGFloat m_borderMarginX;
    CGFloat m_borderMarginY;
    CGFloat m_arrowLength;
    CGPoint m_dialogPosition;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) showDialog:(const ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Values)dialogType :(const std::string*)title :(const std::string*)description;

- (void) closeCurrentDialog;

- (void) setModalBackgroundActive:(BOOL)active;

- (ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsViewInterop*) getInterop;

@property (nonatomic, retain) UIView* pBackgroundContainer;
@property (nonatomic, retain) UIView* pDialogContainer;
@property (nonatomic, retain) UIImageView* pArrowLeft;
@property (nonatomic, retain) UIImageView* pArrowRight;
@property (nonatomic, retain) UIImageView* pArrowUp;
@property (nonatomic, retain) UIImageView* pArrowDown;
@property (nonatomic, retain) UIView* pDialogTextboxContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UITextView* pDescriptionLabel;
@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;

@end
