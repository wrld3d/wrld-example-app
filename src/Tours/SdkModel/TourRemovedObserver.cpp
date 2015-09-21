// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourRemovedObserver.h"
#include "ITourRepository.h"
#include "IWorldPinsService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourRemovedObserver::TourRemovedObserver(ITourRepository& tourRepository,
                                                     WorldPins::SdkModel::IWorldPinsService& worldPinsService)
            : m_tourRepository(tourRepository)
            , m_worldPinsService(worldPinsService)
            , m_binding(this, &TourRemovedObserver::HandleTourRemoved)
            {
                m_tourRepository.InsertItemAddedCallback(m_binding);
            }
            
            TourRemovedObserver::~TourRemovedObserver()
            {
                m_tourRepository.RemoveItemAddedCallback(m_binding);
            }
            
            void TourRemovedObserver::HandleTourRemoved(TourModel& tourModel)
            {
                //m_worldPinsService.RemovePin()
            }
        }
    }
}
