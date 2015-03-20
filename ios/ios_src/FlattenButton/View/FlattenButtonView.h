// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "FlattenButtonViewIncludes.h"

@class FlattenButtonView;

@interface FlattenButtonView : UIButton
{
    ExampleApp::FlattenButton::View::FlattenButtonViewInterop* m_pInterop;
    UIColor* m_pColour;

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

- (ExampleApp::FlattenButton::View::FlattenButtonViewInterop*) getInterop;

- (id) initWithDimensions:(float)width :(float)height :(float)pixelScale;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@end
