// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "WorldPinOnMapView.h"
#include "IWorldPinInFocusViewModel.h"
#include "IScreenControlViewModel.h"
#include "IModalityModel.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewControllerInterop;
	}
}

@interface WorldPinOnMapViewController : UIViewController
{
	ExampleApp::WorldPins::IWorldPinInFocusViewModel* m_pWorldPinInFocusViewModel;
    ExampleApp::WorldPins::WorldPinOnMapViewControllerInterop* m_pInterop;
	ExampleApp::Modality::IModalityModel* m_pModalityModel;
	float m_pinOffset;
	float m_pixelScale;
}

- (id)initWithParams:(ExampleApp::WorldPins::IWorldPinInFocusViewModel*)pWorldPinOnMapInFocusScreenControlViewModel
    :(ExampleApp::ScreenControlViewModel::IScreenControlViewModel*)pSearchResultPoiScreenControlViewModel
    :(ExampleApp::Modality::IModalityModel*)pModalityModel
    :(float)pinDiameter
    :(float)pixelScale;

- (void) open;

- (void) close;

- (void) updateScreenLocation;

- (void) handleScreenStateChanged:(float)screenState;

@property (nonatomic, retain) WorldPinOnMapView* pWorldPinOnMapView;

@end
