// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingViewPerformedRouteQueryMessageHandler.h"
#include "NavRoutingQueryCompletedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingViewPerformedRouteQueryMessageHandler::NavRoutingViewPerformedRouteQueryMessageHandler(SdkModel::INavRoutingServiceController& navRoutingServiceController,
                                                                                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_navRoutingServiceController(navRoutingServiceController)
            , m_messageBus(messageBus)
            , m_routesReceivedCallback(this, &NavRoutingViewPerformedRouteQueryMessageHandler::OnRoutingQueryCompleted)
            , m_routeQueryPerformedMessageHandler(this, &NavRoutingViewPerformedRouteQueryMessageHandler::OnRoutingQueryPerformed)
            {
                m_navRoutingServiceController.RegisterQueryCompletedCallback(m_routesReceivedCallback);
                m_messageBus.SubscribeNative(m_routeQueryPerformedMessageHandler);
            }

            NavRoutingViewPerformedRouteQueryMessageHandler::~NavRoutingViewPerformedRouteQueryMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_routeQueryPerformedMessageHandler);
                m_navRoutingServiceController.UnregisterQueryCompletedCallback(m_routesReceivedCallback);
            }

            void NavRoutingViewPerformedRouteQueryMessageHandler::OnRoutingQueryPerformed(const NavRoutingViewPerformedRouteQueryMessage& message)
            {
                m_navRoutingServiceController.MakeRoutingQuery(message.GetQueryOptions());
            }

            void NavRoutingViewPerformedRouteQueryMessageHandler::OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results)
            {
                m_messageBus.Publish(NavRoutingQueryCompletedMessage(results));
            }
        }
    }
}
