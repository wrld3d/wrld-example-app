// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinOnMapViewModule.h"
#include "IScreenControlViewModel.h"
#include "WorldPinOnMapViewIncludes.h"
#include "IWorldPinInFocusViewModel.h"
#include "Modality.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewModule: public IWorldPinOnMapViewModule, private Eegeo::NonCopyable
		{
		private:
			WorldPinOnMapViewController* m_pWorldPinOnMapViewController;

		public:
			WorldPinOnMapViewModule(
			    AndroidNativeState& nativeState,
			    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
			    ScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
			    Modality::IModalityModel& modalityModel,
			    float pinDiameter
			);

			~WorldPinOnMapViewModule();

			WorldPinOnMapViewController& GetWorldPinOnMapViewController() const;
		};
	}
}
