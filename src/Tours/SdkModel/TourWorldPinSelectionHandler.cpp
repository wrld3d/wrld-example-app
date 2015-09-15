// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourWorldPinSelectionHandler.h"
#include "TourOnMapSelectedMessage.h"
#include "ITourService.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourWorldPinSelectionHandler::TourWorldPinSelectionHandler(TourModel& model,
                                                                       ITourService& tourService,
                                                                       Search::SdkModel::ISearchRefreshService& searchRefreshService)
            : m_model(model)
            , m_tourService(tourService)
            , m_searchRefreshService(searchRefreshService)
            {
                
            }
            
            void TourWorldPinSelectionHandler::SelectPin()
            {
                if(!m_tourService.IsTourActive())
                {
                    // TODO: Don't like this - Extra details about starting a tour that tour service doesn't know about.
                    m_searchRefreshService.SetEnabled(false);
                    m_tourService.StartCurrentActiveTour(m_model, 0);
                }
            }
        }
    }
}
