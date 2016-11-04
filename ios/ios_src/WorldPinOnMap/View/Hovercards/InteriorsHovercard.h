// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"
#include "WorldPinOnMapView.h"
#include "IWorldPinsInFocusModel.h"
#include "BaseHovercard.h"

@class InteriorsHovercard;

@interface InteriorsHovercard : BaseHovercard
{

}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

@property (nonatomic, retain) UILabel* pSubtitleLabel;

@end
