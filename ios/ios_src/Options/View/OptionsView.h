// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Options.h"
#include "AppRunner.h"
#include "UILabelledCheckboxView.h"
#include "OptionsCacheClearSubView.h"

@class OptionsView;
@class OptionsViewController;

@interface OptionsView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::Options::View::OptionsViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (ExampleApp::Options::View::OptionsViewInterop*) getInterop;

- (void) setStreamOverWifiOnlySelected:(bool)isStreamOverWifiOnlySelected;

- (void) setCacheEnabledSelected:(bool)isCacheEnabledSelected;

- (void) setReplayTutorialsSelected:(bool)isReplayTutorialsSelected;

- (bool) isStreamOverWifiOnlySelected;

- (bool) isCacheEnabledSelected;

- (void) concludeCacheClearCeremony;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pOptionsContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabelledCheckboxView* pWifiOnlyCheckbox;
@property (nonatomic, retain) UILabelledCheckboxView* pCacheEnabledCheckbox;
@property (nonatomic, retain) UILabelledCheckboxView* pClearCacheCheckbox;
@property (nonatomic, retain) UILabel* pClearCacheLabel;
@property (nonatomic, retain) OptionsCacheClearSubView* pOptionsCacheClearSubView;

@end
