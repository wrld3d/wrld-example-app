// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "CompassViewIncludes.h"
#include "ViewWrap.h"

@class CompassView;

class CompassViewWrapper : public ViewWrap<CompassView>
{
    using ViewWrap::ViewWrap;
};

@interface CompassView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::Compass::View::CompassViewInterop* m_pInterop;

    UIColor* m_gpsIndicatorColour;

    float m_width;
    float m_height;

    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    float m_yPosBase;

    float m_stateChangeAnimationTimeSeconds;

    float m_compassPointNaturalOffsetX;
    float m_compassPointNaturalOffsetY;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::Compass::View::CompassViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) updateHeading:(float)angleRadians;

- (void) showGpsDisabledView;

- (void) showGpsFollowView;

- (void) showGpsCompassModeView;

- (void) notifyGpsUnauthorized;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

@property (nonatomic, retain) UIImageView* pOuterShape;
@property (nonatomic, retain) UIView* pInnerShape;
@property (nonatomic, retain) UIImageView* pPoint;

@end
