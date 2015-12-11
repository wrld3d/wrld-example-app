// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourWorldPinSelectionHandler.h"
#include "TourOnMapSelectedMessage.h"
#include "ITourService.h"
#include "ISearchRefreshService.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourWorldPinSelectionHandler::TourWorldPinSelectionHandler(TourModel& model,
                                                                       ITourService& tourService,
                                                                       AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_model(model)
            , m_tourService(tourService)
            , m_appModeModel(appModeModel)
            {
                
            }
            
            void TourWorldPinSelectionHandler::SelectPin()
            {
                if(!m_tourService.IsTourActive() && m_model.IsInterior() == (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode))
                {
                    m_tourService.StartCurrentActiveTour(m_model, 0);
                }
            }
        }
    }
}
