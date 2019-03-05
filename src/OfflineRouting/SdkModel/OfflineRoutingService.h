// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "OfflineRouting.h"
#include "RoutingQueryOptions.h"
#include "IRoutingWebservice.h"
#include "RoutingQueryIdGenerator.h"
#include "CallbackCollection.h"

#include <unordered_map>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingService : public Eegeo::Routes::Webservice::IRoutingWebservice, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingService(RoutingEngine::IOfflineRoutingGraphPositioner& offlineRoutingGraphPositioner,
                                      RoutingEngine::IOfflineRoutingPathFinder& offlineRoutingPathFinder,
                                      IOfflineRoutingServiceRouteDataBuilder& routeDataBuilder);

                ~OfflineRoutingService() {}

                Eegeo::Routes::Webservice::RoutingQueryId BeginRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options) override;
                void CancelQuery(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId) override;

                void RegisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback) override;
                void UnregisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback) override;

                void Update(float dt);

            private:
                bool TryFindPointsOnGraph(const std::vector<Eegeo::Routes::Webservice::RoutingQueryWaypoint>& waypoints,
                                          std::vector<RoutingEngine::OfflineRoutingPointOnGraph>& pointsOnGraph);

                bool TryFindPaths(const std::vector<RoutingEngine::OfflineRoutingPointOnGraph> queryPoints,
                                  const Eegeo::Routes::Webservice::TransportationMode& transportationMode,
                                  std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults);

                void ProcessQueries();

                void NotifyQuerySuccess(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId,
                                         const std::vector<Eegeo::Routes::Webservice::RouteData>& routeData);
                void NotifyQueryFailed(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId);

                RoutingEngine::IOfflineRoutingGraphPositioner& m_offlineRoutingGraphPositioner;
                RoutingEngine::IOfflineRoutingPathFinder& m_offlineRoutingPathFinder;
                IOfflineRoutingServiceRouteDataBuilder& m_routeDataBuilder;

                std::unordered_map<Eegeo::Routes::Webservice::RoutingQueryId, Eegeo::Routes::Webservice::RoutingQueryOptions> m_queriesToProcess;

                Eegeo::Routes::Webservice::RoutingQueryIdGenerator m_routingQueryIdGenerator;
                Eegeo::Helpers::CallbackCollection1<const Eegeo::Routes::Webservice::RoutingQueryResponse> m_queryCompletedCallbacks;
            };
        }
    }
}
