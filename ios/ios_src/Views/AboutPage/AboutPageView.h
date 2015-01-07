// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AboutPage.h"
#include "AppRunner.h"
#include "TestCustomView.h"

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

@property (nonatomic, retain) TestCustomView* pTestCustomView;

@end
