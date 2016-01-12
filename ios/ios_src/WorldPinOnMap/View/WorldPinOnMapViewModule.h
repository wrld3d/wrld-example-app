// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinOnMapViewModule.h"
#include "WorldPins.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"
#include "WorldPinOnMapViewIncludes.h"
#include "IAppModeModel.h"
#include "ImageStore.h"
#include "TourHovercardView.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinOnMapViewModule: public IWorldPinOnMapViewModule, private Eegeo::NonCopyable
            {
            private:
                WorldPinOnMapViewContainer* m_pView;
                WorldPinOnMapController* m_pController;
                
                TourHovercardView* m_pTourView;

            public:
                WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                        ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                        Modality::View::IModalityModel& modalityModel,
                                        float pinDiameter,
                                        float pixelScale,
                                        ImageStore* pImageStore);
                
                ~WorldPinOnMapViewModule();

                WorldPinOnMapController& GetWorldPinOnMapController() const;

                WorldPinOnMapViewContainer& GetWorldPinOnMapView() const;
            };
        }
    }
}
