// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinOnMapViewModule.h"
#include "WorldPins.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"
#include "WorldPinOnMapViewIncludes.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewModule: public IWorldPinOnMapViewModule, private Eegeo::NonCopyable
		{
		private:
			WorldPinOnMapViewController* m_pWorldPinOnMapViewController;

		public:
			WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                    ScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                    Modality::IModalityModel& modalityModel,
                                    float pinDiameter,
                                    float pixelScale);

			~WorldPinOnMapViewModule();

			WorldPinOnMapViewController& GetWorldPinOnMapViewController() const;

			WorldPinOnMapView& GetWorldPinOnMapView() const;
		};
	}
}
