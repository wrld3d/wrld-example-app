// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AboutPage.h"
#include "AppRunner.h"

@class AboutPageView;
@class AboutPageViewController;

@interface AboutPageView : UIView
{
	__weak AboutPageViewController* m_pController;
	float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithController:(AboutPageViewController *)controller;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::AboutPage::IAboutPageModel*)pModel;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pShadowContainer;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIImageView* pLogoImage;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabel* pDevelopedByLabel;
@property (nonatomic, retain) UILabel* pTextContent;

@end
