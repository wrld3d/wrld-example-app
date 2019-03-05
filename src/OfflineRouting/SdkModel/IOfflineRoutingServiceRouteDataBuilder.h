// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Routes.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class IOfflineRoutingServiceRouteDataBuilder
            {
            public:
                virtual ~IOfflineRoutingServiceRouteDataBuilder() {}

                virtual std::vector<Eegeo::Routes::Webservice::RouteData> BuildRouteData(const std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults,
                                                                                         const Eegeo::Routes::Webservice::TransportationMode& transportationMode) = 0;
            };
        }
    }
}
