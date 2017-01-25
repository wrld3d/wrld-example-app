// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinOnMapViewModule.h"
#include "WorldPins.h"
#include "WorldPinOnMapViewIncludes.h"
#include "Modality.h"
#include "WindowsNativeState.h"
#include "IScreenControlViewModel.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapViewModule: public IWorldPinOnMapViewModule, private Eegeo::NonCopyable
            {
            private:
                WorldPinOnMapView* m_pView;
                WorldPinOnMapController* m_pController;

            public:
                WorldPinOnMapViewModule(
                    WindowsNativeState& nativeState,
                    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                    ScreenControl::View::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                    Modality::View::IModalityModel& modalityModel,
                    float pinDiameter,
                    bool isInKioskMode
                );

                ~WorldPinOnMapViewModule();

                WorldPinOnMapController& GetWorldPinOnMapController() const;
            };
        }
    }
}
