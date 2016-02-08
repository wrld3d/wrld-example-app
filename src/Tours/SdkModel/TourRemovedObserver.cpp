// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourRemovedObserver.h"
#include "ITourRepository.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourRemovedObserver::TourRemovedObserver(ITourRepository& tourRepository)
            : m_tourRepository(tourRepository)
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
                // TODO: This is not doing anything?
            }
        }
    }
}
