// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "WorldPinOnMapViewModule.h"
#include "IWorldPinInFocusViewModel.h"
#include "WorldPinOnMapViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		WorldPinOnMapViewModule::WorldPinOnMapViewModule(
		    AndroidNativeState& nativeState,
		    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
		    ScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
		    float pinDiameter
		)
		{
			ASSERT_UI_THREAD

			m_pWorldPinOnMapViewController = Eegeo_NEW(WorldPinOnMapViewController)(
			        nativeState,
			        worldPinInFocusViewModel,
			        worldPinOnMapInFocusScreenControlViewModel,
			        pinDiameter
			                                     );
		}

		WorldPinOnMapViewModule::~WorldPinOnMapViewModule()
		{
			ASSERT_UI_THREAD

			Eegeo_DELETE m_pWorldPinOnMapViewController;
		}

		WorldPinOnMapViewController& WorldPinOnMapViewModule::GetWorldPinOnMapViewController() const
		{
			ASSERT_UI_THREAD

			return *m_pWorldPinOnMapViewController;
		}
	}
}
