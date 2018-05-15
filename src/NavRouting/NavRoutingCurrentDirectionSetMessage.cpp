// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingCurrentDirectionSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingCurrentDirectionSetMessage::NavRoutingCurrentDirectionSetMessage(int directionIndex)
        : m_directionIndex(directionIndex)
        {

        }

        int NavRoutingCurrentDirectionSetMessage::GetDirectionIndex() const
        {
            return m_directionIndex;
        }
    }
}
