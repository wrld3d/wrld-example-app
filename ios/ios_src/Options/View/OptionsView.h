// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Options.h"
#include "AppRunner.h"
#include "UILabelledCheckboxView.h"
#include "OptionsCacheClearSubView.h"
#import "CustomSwitch.h"
#import "HeaderView.h"
#include "MessageView.h"

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

- (bool) isStreamOverWifiOnlySelected;

- (bool) isCacheEnabledSelected;

- (void) openClearCacheWarning;

- (void) concludeCacheClearCeremony;

@property (nonatomic, retain) HeaderView* pHeaderView;

@property (nonatomic, retain) CustomSwitch*  pWifiOnlySwitch;
@property (nonatomic, retain) CustomSwitch* pCacheEnabledSwitch;
@property (nonatomic, retain) UIButton* pClearCacheButton;
@property (nonatomic, retain) UIButton* pReplayTutorialsButton;

@property (nonatomic, retain) UILabel*  pWifiOnlyLabel;
@property (nonatomic, retain) UILabel*  pCacheEnabledLabel;
@property (nonatomic, retain) UILabel*  pClearCacheLabel;
@property (nonatomic, retain) UILabel*  pReplayTutorialsLabel;

@property (nonatomic, retain) UIView* pContentContainer;

@property (nonatomic, retain) OptionsCacheClearSubView* pOptionsCacheClearSubView;
@property (nonatomic, retain) MessageView* pReplayTutorialsMessage;
@end
