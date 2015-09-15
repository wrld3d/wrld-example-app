// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourHovercardViewModule.h"
#include "WorldPinOnMapController.h"
#include "TourHovercardView.h"
#include "TourHovercardViewInterop.h"
#include "ITourHovercardView.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                TourHovercardViewModule::TourHovercardViewModule(WorldPins::View::IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                                                 ScreenControl::View::IScreenControlViewModel::IScreenControlViewModel& worldPinOnMapInFocusScreenControlViewModel,
                                                                 Modality::View::IModalityModel& modalityModel,
                                                                 float pinDiameter,
                                                                 float pixelScale,
                                                                 const AppModes::SdkModel::IAppModeModel& appModeModel)
                {
                    m_pView = [[TourHovercardView alloc] initWithParams:pinDiameter :pixelScale];
                    
                    m_pController = Eegeo_NEW(WorldPins::View::WorldPinOnMapController)(
                                                                       *[m_pView getInterop],
                                                                       worldPinInFocusViewModel,
                                                                       worldPinOnMapInFocusScreenControlViewModel,
                                                                       modalityModel,
                                                                       appModeModel);
                }
                
                TourHovercardViewModule::~TourHovercardViewModule()
                {
                    Eegeo_DELETE m_pController;
                    [m_pView release];
                }
                
                WorldPins::View::WorldPinOnMapController& TourHovercardViewModule::GetWorldPinOnMapController() const
                {
                    return *m_pController;
                }
                
                TourHovercardView& TourHovercardViewModule::GetTourHovercardView() const
                {
                    return *m_pView;
                }
                
                ITourHovercardView& TourHovercardViewModule::GetTourHovercardViewInterop() const
                {
                    return *[m_pView getInterop];
                }
            }
        }
    }
}