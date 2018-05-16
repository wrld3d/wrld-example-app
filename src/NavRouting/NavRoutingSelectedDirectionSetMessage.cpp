// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingSelectedDirectionSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingSelectedDirectionSetMessage::NavRoutingSelectedDirectionSetMessage(int directionIndex)
                : m_directionIndex(directionIndex)
        {

        }

        int NavRoutingSelectedDirectionSetMessage::GetDirectionIndex() const
        {
            return m_directionIndex;
        }
    }
}
