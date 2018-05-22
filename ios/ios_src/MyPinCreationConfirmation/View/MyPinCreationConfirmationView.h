// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationConfirmationViewIncludes.h"

@class MyPinCreationConfirmationView;

@interface MyPinCreationConfirmationView : UIView
{
    ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop* m_pInterop;

    CGFloat m_screenWidth;
    CGFloat m_screenHeight;
    
    CGFloat m_offscreen_offset;

    float m_stateChangeAnimationTimeSeconds;
}

- (instancetype) initWithScreenWidth:(CGFloat)width screenHeight:(CGFloat)height;

- (ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

@property(nonatomic, retain) UILabel* pTitleBarText;
@property(nonatomic, retain) UIView* pMainSection;
@property(nonatomic, retain) UIButton* pCancelButton;
@property(nonatomic, retain) UIButton* pConfirmButton;

@end
