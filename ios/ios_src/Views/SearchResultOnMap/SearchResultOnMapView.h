// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"

@class SearchResultOnMapView;
@class SearchResultOnMapViewController;

@interface SearchResultOnMapView : UIView
{
    __weak SearchResultOnMapViewController* m_pController;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithController:(SearchResultOnMapViewController *)controller;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setLabel:(std::string)name :(std::string)detail; 

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pTopStrip;
@property (nonatomic, retain) UIView* pMainControlShadowContainer;
@property (nonatomic, retain) UIView* pArrowContainer;
@property (nonatomic, retain) UIView* pLabelBack;
@property (nonatomic, retain) UILabel* pNameLabel;
@property (nonatomic, retain) UILabel* pAddressLabel;

@end
