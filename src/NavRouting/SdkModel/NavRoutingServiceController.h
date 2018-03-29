// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "NavRouting.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingServiceController : private Eegeo::NonCopyable
            {
            public:
                NavRoutingServiceController(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice);

                ~NavRoutingServiceController();
                
                void MakeRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options);
                
                void RegisterQueryCompletedCallback(RoutesReceivedCallback& callback);
                void UnregisterQueryCompletedCallback(RoutesReceivedCallback& callback);
                
            private:
                
                void OnRoutingQueryCompleted(const Eegeo::Routes::Webservice::RoutingQueryResponse& results);
                
                Eegeo::Routes::Webservice::IRoutingWebservice& m_routingWebservice;
                
                Eegeo::Helpers::TCallback1<NavRoutingServiceController, const Eegeo::Routes::Webservice::RoutingQueryResponse> m_routingQueryCompleted;
                
                Eegeo::Routes::Webservice::RoutingQueryId m_routingQueryId;
                
                Eegeo::Helpers::CallbackCollection1<const std::vector<Eegeo::Routes::Webservice::RouteData>> m_routingQueryCompletedCallbacks;
            };
        }
    }
}
