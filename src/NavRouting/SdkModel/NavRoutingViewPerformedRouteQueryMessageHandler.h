// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "RouteData.h"
#include "BidirectionalBus.h"
#include "INavRoutingServiceController.h"
#include "NavRoutingViewPerformedRouteQueryMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingViewPerformedRouteQueryMessageHandler
            {
            public:
                NavRoutingViewPerformedRouteQueryMessageHandler(SdkModel::INavRoutingServiceController& navRoutingServiceController,
                                                                ExampleAppMessaging::TMessageBus& messageBus);

                ~NavRoutingViewPerformedRouteQueryMessageHandler();

            private:

                SdkModel::INavRoutingServiceController& m_navRoutingServiceController;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<NavRoutingViewPerformedRouteQueryMessageHandler, const std::vector<Eegeo::Routes::Webservice::RouteData>> m_routesReceivedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingViewPerformedRouteQueryMessageHandler, const NavRoutingViewPerformedRouteQueryMessage&> m_routeQueryPerformedMessageHandler;

                void OnRoutingQueryPerformed(const NavRoutingViewPerformedRouteQueryMessage& message);

                void OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results);
            };
        }
    }
}
