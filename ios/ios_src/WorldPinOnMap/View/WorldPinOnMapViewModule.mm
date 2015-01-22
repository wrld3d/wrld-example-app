// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinOnMapViewModule.h"
#include "IWorldPinInFocusViewModel.h"
#include "WorldPinOnMapViewController.h"
#include "IModalityModel.h"

namespace ExampleApp
{
	namespace WorldPins
	{
        WorldPinOnMapViewModule::WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                                         ScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                                         Modality::IModalityModel& modalityModel,
                                                         float pinDiameter,
                                                         float pixelScale)
		{
			m_pWorldPinOnMapViewController = [[WorldPinOnMapViewController alloc] initWithParams
			                                      :&worldPinInFocusViewModel
			                                      :&worldPinOnMapInFocusScreenControlViewModel
			                                      :&modalityModel
			                                      :pinDiameter
			                                      :pixelScale];
		}

		WorldPinOnMapViewModule::~WorldPinOnMapViewModule()
		{
			[m_pWorldPinOnMapViewController release];
		}

		WorldPinOnMapViewController& WorldPinOnMapViewModule::GetWorldPinOnMapViewController() const
		{
			return *m_pWorldPinOnMapViewController;
		}

		WorldPinOnMapView& WorldPinOnMapViewModule::GetWorldPinOnMapView() const
		{
			return *[m_pWorldPinOnMapViewController pWorldPinOnMapView];
		}
	}
}
