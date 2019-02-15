// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingService.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            OfflineRoutingService::OfflineRoutingService(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice)
            : m_routingWebservice(routingWebservice)
            {
            }

            Eegeo::Routes::Webservice::RoutingQueryId OfflineRoutingService::BeginRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options)
            {
                return m_routingWebservice.BeginRoutingQuery(options);
            }

            void OfflineRoutingService::CancelQuery(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId)
            {
                m_routingWebservice.CancelQuery(routingQueryId);
            }

            void OfflineRoutingService::RegisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback)
            {
                m_routingWebservice.RegisterQueryCompletedCallback(callback);
            }

            void OfflineRoutingService::UnregisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback)
            {
                m_routingWebservice.UnregisterQueryCompletedCallback(callback);
            }
        }
    }
}
