// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "ModalBackgroundViewController.h"

@class ModalBackgroundView;

@interface ModalBackgroundView : UIView
{
    __weak ModalBackgroundViewController* m_pController;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithController:(ModalBackgroundViewController *)controller;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@end