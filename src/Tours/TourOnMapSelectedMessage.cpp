// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourModel.h"
#include "TourOnMapSelectedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        TourOnMapSelectedMessage::TourOnMapSelectedMessage(const SdkModel::TourModel& tourModel, const int initialCard, bool showBackButton)
        : m_tourModel(tourModel)
        , m_initialCard(initialCard)
        , m_showBackButton(showBackButton)
        {
            
        }
        
        const SdkModel::TourModel& TourOnMapSelectedMessage::GetTourModel() const
        {
            return m_tourModel;
        }
        
        const int TourOnMapSelectedMessage::GetInitialCard() const
        {
            return m_initialCard;
        }
        
        bool TourOnMapSelectedMessage::GetShowBackButton() const
        {
            return m_showBackButton;
        }
    }
}
