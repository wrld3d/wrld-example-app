// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewModule.h"
#include "IWorldPinInFocusViewModel.h"
#include "WorldPinOnMapView.h"
#include "WorldPinOnMapController.h"
#include "WorldPinOnMapViewInterop.h"
#include "IModalityModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapViewModule::WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                    ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                    Modality::View::IModalityModel& modalityModel,
                    const AppModes::SdkModel::IAppModeModel& appModeModel,
                    float pinDiameter,
                    float pixelScale)
            {
                m_pView = [[WorldPinOnMapView alloc] initWithParams:pinDiameter :pixelScale];

                m_pController = Eegeo_NEW(WorldPinOnMapController)(
                                    *[m_pView getInterop],
                                    worldPinInFocusViewModel,
                                    worldPinOnMapInFocusScreenControlViewModel,
                                    modalityModel,
                                    appModeModel);
            }

            WorldPinOnMapViewModule::~WorldPinOnMapViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            WorldPinOnMapController& WorldPinOnMapViewModule::GetWorldPinOnMapController() const
            {
                return *m_pController;
            }

            WorldPinOnMapView& WorldPinOnMapViewModule::GetWorldPinOnMapView() const
            {
                return *m_pView;
            }
        }
    }
}
