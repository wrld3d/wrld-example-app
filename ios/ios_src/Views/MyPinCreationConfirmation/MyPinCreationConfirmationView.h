// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationConfirmationViewController.h"

@class MyPinCreationConfirmationView;

@interface MyPinCreationConfirmationView : UIView
{
    __weak MyPinCreationConfirmationViewController* m_pController;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithParams:(MyPinCreationConfirmationViewController *)controller :(float)width :(float)height :(float)pixelScale;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@property(nonatomic, retain) UIView* pTitleBar;
@property(nonatomic, retain) UILabel* pTitleBarText;
@property(nonatomic, retain) UIView* pMainSection;
@property(nonatomic, retain) UIButton* pCancelButton;
@property(nonatomic, retain) UIButton* pConfirmButton;

@end