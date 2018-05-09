// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingQueryCompletedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingQueryCompletedMessage::NavRoutingQueryCompletedMessage(const std::vector<Eegeo::Routes::Webservice::RouteData>& routeData)
                : m_routeData(routeData)
        {

        }

        const std::vector<Eegeo::Routes::Webservice::RouteData>& NavRoutingQueryCompletedMessage::GetRouteData() const
        {
            return m_routeData;
        }
    }
}
