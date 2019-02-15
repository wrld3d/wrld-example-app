// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "OfflineRouting.h"
#include "IRoutingWebservice.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingService : public Eegeo::Routes::Webservice::IRoutingWebservice, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingService(Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice);

                ~OfflineRoutingService() {}

                Eegeo::Routes::Webservice::RoutingQueryId BeginRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options) override;
                void CancelQuery(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId) override;

                void RegisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback) override;
                void UnregisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback) override;

            private:
                Eegeo::Routes::Webservice::IRoutingWebservice& m_routingWebservice;
            };
        }
    }
}
