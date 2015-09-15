// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourActiveStateChangedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        TourActiveStateChangedMessage::TourActiveStateChangedMessage(int activeStateIndex)
        : m_activeStateIndex(activeStateIndex)
        {
            
        }
        
        int TourActiveStateChangedMessage::GetActiveStateIndex() const
        {
            return m_activeStateIndex;
        }
    }
}
