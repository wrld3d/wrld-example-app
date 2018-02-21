// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Options.h"
#include "AppRunner.h"

#include "OptionsCacheClearSubView.h"
#import "CustomSwitch.h"

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

- (void) setClearCacheSelected:(bool)isclearCacheSelected;

- (void) setReplayTutorialsSelected:(bool)isReplayTutorialsSelected;

- (bool) isStreamOverWifiOnlySelected;

- (bool) isCacheEnabledSelected;

- (bool) isClearCacheSelected;

- (void) openClearCacheWarning;

- (void) concludeCacheClearCeremony;


@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UIView* pHeaderView;


@property (nonatomic, retain) UIView* pHeaderSeparator;
@property (nonatomic, retain) UIView* pContentSeparator;


@property (nonatomic, retain) CustomSwitch*  pWifiOnlySwitch;
@property (nonatomic, retain) CustomSwitch* pCacheEnabledSwitch;
@property (nonatomic, retain) CustomSwitch* pClearCacheCheckbox;
@property (nonatomic, retain) CustomSwitch* pReplayTutorialsCheckbox;

@property (nonatomic, retain) UILabel*  pWifiOnlyLabel;
@property (nonatomic, retain) UILabel*  pCacheEnabledLabel;
@property (nonatomic, retain) UILabel*  pClearCacheLabel;
@property (nonatomic, retain) UILabel*  pReplayTutorialsLabel;

@property (nonatomic, retain) UIView* pContentContainer;

@property (nonatomic, retain) UIButton* pTickButton;

@property (nonatomic, retain) OptionsCacheClearSubView* pOptionsCacheClearSubView;

@end
