// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "PoiCreationButtonViewController.h"

@class PoiCreationButtonView;

@interface PoiCreationButtonView : UIView
{
    __weak PoiCreationButtonViewController* m_pController;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    float m_yPosBase;
    
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithParams:(PoiCreationButtonViewController *)controller :(float)width :(float)height :(float)pixelScale;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

- (void) shouldOffsetButton:(bool)shouldOffset;

@property (nonatomic, retain) UIButton* pPoiCreateButton;

@end