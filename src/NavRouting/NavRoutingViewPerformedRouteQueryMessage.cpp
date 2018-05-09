// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingViewPerformedRouteQueryMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingViewPerformedRouteQueryMessage::NavRoutingViewPerformedRouteQueryMessage(const Eegeo::Routes::Webservice::RoutingQueryOptions& queryOptions)
                : m_queryOptions(queryOptions)
        {

        }

        const Eegeo::Routes::Webservice::RoutingQueryOptions& NavRoutingViewPerformedRouteQueryMessage::GetQueryOptions() const
        {
            return m_queryOptions;
        }
    }
}
