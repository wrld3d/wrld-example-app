// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"
#include "IWorldPinsInFocusModel.h"
#include "YelpHovercardView.h"
#include "InteriorsHovercard.h"
#include "TourHovercardView.h"
#include "ImageStore.h"

@class WorldPinOnMapViewContainer;

@interface WorldPinOnMapViewContainer : UIView
{
    ExampleApp::WorldPins::View::WorldPinOnMapViewInterop* m_pInterop;
    CGFloat m_screenWidth;
    CGFloat m_screenHeight;
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore;

- (ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

@property (nonatomic, retain) YelpHovercardView* pYelpHovercard;
@property (nonatomic, retain) InteriorsHovercard* pInteriorHovercard;
@property (nonatomic, retain) TourHovercardView* pTourHovercard;
@property (nonatomic, retain) UIView* pTwitterHovercard;
@property (nonatomic, retain) UIView* pTwitterTourHovercard;
@property (nonatomic, retain) UIView<WorldPinOnMapView>* pCurrentHovercard;

@end
