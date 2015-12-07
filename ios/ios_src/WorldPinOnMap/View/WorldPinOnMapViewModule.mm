// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewModule.h"
#include "IWorldPinInFocusViewModel.h"
#include "WorldPinOnMapView.h"
#include "WorldPinOnMapController.h"
#include "WorldPinOnMapViewInterop.h"
#include "IModalityModel.h"
#include "TourHovercardView.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapViewModule::WorldPinOnMapViewModule(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                    ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                    Modality::View::IModalityModel& modalityModel,
                    float pinDiameter,
                    float pixelScale,
                    ImageStore* pImageStore)
            {
                m_pView = [[WorldPinOnMapViewContainer alloc] initWithParams:pinDiameter :pixelScale :pImageStore];

                m_pController = Eegeo_NEW(WorldPinOnMapController)(
                                    *[m_pView getInterop],
                                    worldPinInFocusViewModel,
                                    worldPinOnMapInFocusScreenControlViewModel,
                                    modalityModel);
            }

            WorldPinOnMapViewModule::~WorldPinOnMapViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pTourView release];
            }

            WorldPinOnMapController& WorldPinOnMapViewModule::GetWorldPinOnMapController() const
            {
                return *m_pController;
            }

            WorldPinOnMapViewContainer& WorldPinOnMapViewModule::GetWorldPinOnMapView() const
            {
                return *m_pView;
            }
        }
    }
}
