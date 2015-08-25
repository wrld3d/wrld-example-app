// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewModule.h"
#include "WorldPinOnMapView.h"
#include "WorldPinOnMapController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapViewModule::WorldPinOnMapViewModule(
                AndroidNativeState& nativeState,
                IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                ScreenControl::View::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                Modality::View::IModalityModel& modalityModel,
                const AppModes::SdkModel::IAppModeModel& appModeModel,
                float pinDiameter
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(WorldPinOnMapView)(nativeState, pinDiameter);
                m_pController = Eegeo_NEW(WorldPinOnMapController)(*m_pView, worldPinInFocusViewModel, worldPinOnMapInFocusScreenControlViewModel, modalityModel, appModeModel);
            }

            WorldPinOnMapViewModule::~WorldPinOnMapViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            WorldPinOnMapController& WorldPinOnMapViewModule::GetWorldPinOnMapController() const
            {
                ASSERT_UI_THREAD

                return *m_pController;
            }
        }
    }
}
