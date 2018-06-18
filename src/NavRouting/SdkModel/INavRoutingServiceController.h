// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "NavRouting.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingServiceController
            {
            public:
                virtual ~INavRoutingServiceController() { }

                virtual void MakeRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options) = 0;
                virtual void CancelRoutingQuery() = 0;

                virtual void RegisterQueryCompletedCallback(RoutesReceivedCallback& callback) = 0;
                virtual void UnregisterQueryCompletedCallback(RoutesReceivedCallback& callback) = 0;
                virtual void RegisterQueryFailedCallback(RouteFailedCallback& callback) = 0;
                virtual void UnregisterQueryFailedCallback(RouteFailedCallback& callback) = 0;
            };
        }
    }
}
