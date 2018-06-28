// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingSetCalculatingRouteMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingSetCalculatingRouteMessage::NavRoutingSetCalculatingRouteMessage(bool calculatingRoute)
        : m_calculatingRoute(calculatingRoute)
        {

        }

        bool NavRoutingSetCalculatingRouteMessage::GetShouldCalculatingRoute() const
        {
            return m_calculatingRoute;
        }
    }
}
