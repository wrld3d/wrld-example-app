// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "CompassViewController.h"

@class CompassView;

@interface CompassView : UIView
{
    __weak CompassViewController* m_pController;
    
    UIColor* m_darkColour;
    UIColor* m_lightColour;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    
    float m_stateChangeAnimationTimeSeconds;
    
    float m_compassPointNaturalOffsetX;
    float m_compassPointNaturalOffsetY;
}

- (id) initWithParams:(CompassViewController *)controller :(float)width :(float)height :(float)pixelScale;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) updateHeading:(float)angleRadians;

- (void) showGpsDisabledView;

- (void) showGpsFollowView;

- (void) showGpsCompassModeView;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@property (nonatomic, retain) UIView* pOuterShape;
@property (nonatomic, retain) UIView* pOuterShadowContainer;
@property (nonatomic, retain) UIView* pInnerShape;
@property (nonatomic, retain) UIView* pPoint;
@property (nonatomic, retain) UIView* pPointShadowContainer;
@property (nonatomic, retain) UIView* pLockIconContainer;

@end
