// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"

@protocol WorldPinOnMapView

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

@end
