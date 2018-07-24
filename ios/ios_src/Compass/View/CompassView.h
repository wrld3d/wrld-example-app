// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "CompassViewIncludes.h"
#include "IScreenControlView.h"

@class CompassView;

@interface CompassView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::Compass::View::CompassViewInterop* m_pInterop;

    float m_width;
    float m_height;
    
    float m_innerHeight;
    float m_innerWidth;

    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    float m_yPosBase;

    float m_stateChangeAnimationTimeSeconds;

    float m_compassPointNaturalOffsetX;
    float m_compassPointNaturalOffsetY;
    bool m_animatingOnScreen;
    UIViewController* m_rootViewController;
}

enum CompassPositionState {CompassPositionStateDefault, CompassPositionStateNavigation};

- (id) initWithParams:(float)width :(float)height :(float)pixelScale :(UIViewController*)rootViewController;

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

- (void) setRotationHighlight:(bool)shouldShowRotationHighlight;

- (BOOL) isValidPositionState: (ExampleApp::ScreenControl::View::TScreenControlViewState) state;

- (void) setPositionState: (CompassPositionState) state;

- (void) setNavigationModeCompassPosition: (CGFloat) position;

@property (nonatomic, retain) UIImageView* pOuterShape;
@property (nonatomic, retain) UIView* pInnerShape;
@property (nonatomic, retain) UIImageView* pPoint;

@end
