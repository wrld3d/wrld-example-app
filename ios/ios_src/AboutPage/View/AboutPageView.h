// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AboutPage.h"
#include "AppRunner.h"

@class AboutPageView;
@class AboutPageViewController;

@interface AboutPageView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::AboutPage::View::AboutPageViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string*)content;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (void) showHiddenText:(UILongPressGestureRecognizer*)gesture;

- (ExampleApp::AboutPage::View::AboutPageViewInterop*) getInterop;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIImageView* pLogoImage;
@property (nonatomic, retain) UIButton* pLogoButton;;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabel* pDevelopedByLabel;
@property (nonatomic, retain) UILabel* pTextContent;
@property (nonatomic, retain) UILabel* pPrivacyLink;
@property (nonatomic, retain) UILabel* pEulaLink;
@property (nonatomic, retain) UILabel* pLegalLink;
@property (nonatomic, retain) UILabel* pTeamLink;

@end
