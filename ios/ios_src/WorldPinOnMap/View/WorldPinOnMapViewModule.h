// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinOnMapViewModule.h"
#include "WorldPins.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"
#include "WorldPinOnMapViewIncludes.h"
#include "InteriorsExplorer.h"
#include "Interiors.h"

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
                WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                        ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                        Modality::View::IModalityModel& modalityModel,
                                        Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                        float pinDiameter,
                                        float pixelScale);

                ~WorldPinOnMapViewModule();

                WorldPinOnMapController& GetWorldPinOnMapController() const;

                WorldPinOnMapView& GetWorldPinOnMapView() const;
            };
        }
    }
}
