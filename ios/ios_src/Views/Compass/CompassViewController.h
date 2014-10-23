// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "Compass.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"

@class CompassView;

@interface CompassViewController : UIViewController
{
    ExampleApp::Compass::ICompassModel* m_pModel;
    ExampleApp::Compass::ICompassViewModel* m_pViewModel;
    ExampleApp::Compass::CompassViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::Compass::ICompassModel*)pModel
                    :(ExampleApp::Compass::ICompassViewModel*)pViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleGpsModeChanged;

- (void) updateHeading:(float)angleRadians;

- (void) handleScreenStateChanged:(float)onScreenState;

@property (nonatomic, retain) CompassView* pCompassView;

@end
