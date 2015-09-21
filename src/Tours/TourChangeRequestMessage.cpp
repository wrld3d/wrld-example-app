// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourChangeRequestMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        TourChangeRequestMessage::TourChangeRequestMessage(const std::string& tourName)
        : m_tourName(tourName)
        {
            
        }
                
        const std::string TourChangeRequestMessage::GetTourName() const
        {
            return m_tourName;
        }
    }
}
