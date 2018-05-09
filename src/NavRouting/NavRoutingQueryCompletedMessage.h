// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RouteData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingQueryCompletedMessage
        {
        private:
            std::vector<Eegeo::Routes::Webservice::RouteData> m_routeData;

        public:
            NavRoutingQueryCompletedMessage(const std::vector<Eegeo::Routes::Webservice::RouteData>& routeData);

            const std::vector<Eegeo::Routes::Webservice::RouteData>& GetRouteData() const;
        };
    }
}
