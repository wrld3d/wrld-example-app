// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationInitiationViewIncludes.h"

@class MyPinCreationInitiationView;

@interface MyPinCreationInitiationView : UIView
{
    ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewInterop* m_pInterop;

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

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@property (nonatomic, retain) UIButton* pPoiCreateButton;

@end