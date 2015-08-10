// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"

@class WorldPinOnMapView;

@interface WorldPinOnMapView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::WorldPins::View::WorldPinOnMapViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
    float m_pinOffset;
    float m_pixelScale;
    float m_previousX;
    float m_previousY;
    bool m_enlarged;
    float m_cardHeight;
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale;

- (ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string&)name :(const std::string&)subtitle :(const std::string&)ratingsImage :(const int)reviewCount;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pTopStrip;
@property (nonatomic, retain) UIView* pMainControlShadowContainer;
@property (nonatomic, retain) UIView* pArrowContainer;
@property (nonatomic, retain) UIView* pLabelBack;
@property (nonatomic, retain) UILabel* pNameLabel;
@property (nonatomic, retain) UILabel* pAddressLabel;
@property (nonatomic, retain) UIImageView* pImageDisplay;
@property (nonatomic, retain) UILabel* pReviewCountLabel;
@property (nonatomic, retain) UIImageView* pAccreditationImage;


@end
