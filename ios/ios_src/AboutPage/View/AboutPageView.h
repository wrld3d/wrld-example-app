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
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string*)content;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (ExampleApp::AboutPage::View::AboutPageViewInterop*) getInterop;

@property (nonatomic, strong) IBOutlet UILabel *pTextContent;
@property (nonatomic, strong) IBOutlet UIButton *pCloseButton;

@end
