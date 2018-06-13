// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingRerouteDialogClosedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingRerouteDialogClosedMessage::NavRoutingRerouteDialogClosedMessage(bool shouldReroute)
        : m_shouldReroute(shouldReroute)
        {

        }

        bool NavRoutingRerouteDialogClosedMessage::GetShouldReroute() const
        {
            return m_shouldReroute;
        }
    }
}
