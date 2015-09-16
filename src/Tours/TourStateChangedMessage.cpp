// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourStateChangedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        TourStateChangedMessage::TourStateChangedMessage(bool tourStarted)
        : m_tourStarted(tourStarted)
        {
        }
        
        const bool TourStateChangedMessage::TourStarted() const
        {
            return m_tourStarted;
        }
    }
}