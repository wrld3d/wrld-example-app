// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingSelectedDirectionChangedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingSelectedDirectionChangedMessage::NavRoutingSelectedDirectionChangedMessage(int directionIndex)
        : m_directionIndex(directionIndex)
        {

        }

        int NavRoutingSelectedDirectionChangedMessage::GetDirectionIndex() const
        {
            return m_directionIndex;
        }
    }
}
