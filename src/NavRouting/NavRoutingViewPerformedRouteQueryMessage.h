// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RoutingQueryOptions.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingViewPerformedRouteQueryMessage
        {
        private:
            Eegeo::Routes::Webservice::RoutingQueryOptions m_queryOptions;

        public:
            NavRoutingViewPerformedRouteQueryMessage(const Eegeo::Routes::Webservice::RoutingQueryOptions& queryOptions);

            const Eegeo::Routes::Webservice::RoutingQueryOptions& GetQueryOptions() const;
        };
    }
}
