// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "NavRouting.h"
#include "CallbackCollection.h"
#include "INavRoutingServiceController.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingServiceController : public INavRoutingServiceController, private Eegeo::NonCopyable
            {
            public:
                NavRoutingServiceController(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                            ExampleAppMessaging::TMessageBus& messageBus);

                ~NavRoutingServiceController();
                
                void MakeRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options) override;
                void CancelRoutingQuery() override;
                
                void RegisterQueryCompletedCallback(RoutesReceivedCallback& callback) override;
                void UnregisterQueryCompletedCallback(RoutesReceivedCallback& callback) override;
                void RegisterQueryFailedCallback(RouteFailedCallback& callback) override;
                void UnregisterQueryFailedCallback(RouteFailedCallback& callback) override;
                
            private:
                
                void OnRoutingQueryCompleted(const Eegeo::Routes::Webservice::RoutingQueryResponse& results);
                
                Eegeo::Routes::Webservice::IRoutingWebservice& m_routingWebservice;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback1<NavRoutingServiceController, const Eegeo::Routes::Webservice::RoutingQueryResponse> m_routingQueryCompleted;
                
                Eegeo::Routes::Webservice::RoutingQueryId m_routingQueryId;
                
                Eegeo::Helpers::CallbackCollection1<const std::vector<Eegeo::Routes::Webservice::RouteData>> m_routingQueryCompletedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_routingQueryFailedCallbacks;
                
                void ShowCalculatingRouteMesage();
                void HideCalculatingRouteMesage();
            };
        }
    }
}
