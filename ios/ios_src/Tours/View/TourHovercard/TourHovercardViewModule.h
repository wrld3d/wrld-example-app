// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourHovercardViewModule.h"
#include "Modality.h"
#include "IScreenControlViewModel.h"
#include "TourHovercardViewIncludes.h"
#include "IWorldPinOnMapView.h"
#include "TourWebViewIncludes.h"
#include "AppModes.h"
#include "ImageStore.h"

@class ImageStore;

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                class TourHovercardViewModule : public ITourHovercardViewModule, private Eegeo::NonCopyable
                {
                private:
                    TourHovercardView* m_pView;
                    WorldPins::View::WorldPinOnMapController* m_pController;
                    
                public:
                    TourHovercardViewModule(WorldPins::View::IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                            ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                            Modality::View::IModalityModel& modalityModel,
                                            float pinDiameter,
                                            float pixelScale,
                                            ImageStore* pImageStore,
                                            const AppModes::SdkModel::IAppModeModel& appModeModel);
                    
                    ~TourHovercardViewModule();
                    
                    WorldPins::View::WorldPinOnMapController& GetWorldPinOnMapController() const;
                    
                    ITourHovercardView& GetTourHovercardViewInterop() const;
                    
                    TourHovercardView& GetTourHovercardView() const;
                };
            }
        }
    }
}