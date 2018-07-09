// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingServiceController.h"

#include "IRoutingWebservice.h"
#include "RoutingQueryResponse.h"
#include "NavRoutingSetCalculatingRouteMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingServiceController::NavRoutingServiceController(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_routingWebservice(routingWebservice)
            , m_routingQueryCompleted(this, &NavRoutingServiceController::OnRoutingQueryCompleted)
            , m_messageBus(messageBus)
            {
                m_routingQueryId = 0;
                
                m_routingWebservice.RegisterQueryCompletedCallback(m_routingQueryCompleted);
            }

            NavRoutingServiceController::~NavRoutingServiceController()
            {
                m_routingWebservice.UnregisterQueryCompletedCallback(m_routingQueryCompleted);
            }
            
            void NavRoutingServiceController::MakeRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options)
            {
                CancelRoutingQuery();
                ShowCalculatingRouteMesage();
                m_routingQueryId = m_routingWebservice.BeginRoutingQuery(options);
            }

            void NavRoutingServiceController::CancelRoutingQuery()
            {
                if (m_routingQueryId!=0)
                {
                    m_routingWebservice.CancelQuery(m_routingQueryId);
                    HideCalculatingRouteMesage();
                }
            }
            
            void NavRoutingServiceController::OnRoutingQueryCompleted(const Eegeo::Routes::Webservice::RoutingQueryResponse& results)
            {
                if (results.Id == m_routingQueryId)
                {
                    if (results.Succeeded &&
                        results.Results.size() > 0 &&
                        results.Results.front().Distance > 0.0)
                    {
                        m_routingQueryCompletedCallbacks.ExecuteCallbacks(results.Results);
                    }
                    else
                    {
                        m_routingQueryFailedCallbacks.ExecuteCallbacks();
                    }
                    HideCalculatingRouteMesage();
                    m_routingQueryId = 0;
                }
            }
            
            void NavRoutingServiceController::RegisterQueryCompletedCallback(RoutesReceivedCallback& callback)
            {
                m_routingQueryCompletedCallbacks.AddCallback(callback);
            }
            
            void NavRoutingServiceController::UnregisterQueryCompletedCallback(RoutesReceivedCallback& callback)
            {
                m_routingQueryCompletedCallbacks.RemoveCallback(callback);
            }

            void NavRoutingServiceController::RegisterQueryFailedCallback(RouteFailedCallback& callback)
            {
                m_routingQueryFailedCallbacks.AddCallback(callback);
            }

            void NavRoutingServiceController::UnregisterQueryFailedCallback(RouteFailedCallback& callback)
            {
                m_routingQueryFailedCallbacks.RemoveCallback(callback);
            }
            
            void NavRoutingServiceController::ShowCalculatingRouteMesage()
            {
                m_messageBus.Publish(NavRoutingSetCalculatingRouteMessage(true));
            }
            void NavRoutingServiceController::HideCalculatingRouteMesage()
            {
                m_messageBus.Publish(NavRoutingSetCalculatingRouteMessage(false));
            }
        }
    }
}
