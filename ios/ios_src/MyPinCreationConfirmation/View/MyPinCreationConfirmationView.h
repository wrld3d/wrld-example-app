// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationConfirmationViewIncludes.h"

@class MyPinCreationConfirmationView;

@interface MyPinCreationConfirmationView : UIView
{
    ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop* m_pInterop;

    float m_width;
    float m_height;

    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;

    float m_yPosActive;
    float m_yPosInactive;

    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@property(nonatomic, retain) UILabel* pTitleBarText;
@property(nonatomic, retain) UIView* pMainSection;
@property(nonatomic, retain) UIButton* pCancelButton;
@property(nonatomic, retain) UIButton* pConfirmButton;

@end