// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IOfflineRoutingServiceRouteDataBuilder.h"
#include "Routes.h"
#include "Types.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class OfflineRoutingServiceRouteDataBuilder : public IOfflineRoutingServiceRouteDataBuilder, private Eegeo::NonCopyable
            {
            public:
                OfflineRoutingServiceRouteDataBuilder(const RoutingEngine::IOfflineRoutingDataRepository& offlineRoutingDataRepository);
                ~OfflineRoutingServiceRouteDataBuilder() {}

                std::vector<Eegeo::Routes::Webservice::RouteData> BuildRouteData(const std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults,
                                                                                 const Eegeo::Routes::Webservice::TransportationMode& transportationMode) override;

            private:
                std::vector<Eegeo::Routes::Webservice::RouteStep> BuildRouteSteps(const RoutingEngine::OfflineRoutingPointOnGraph& startPoint,
                                                                                  const RoutingEngine::OfflineRoutingPointOnGraph& endPoint,
                                                                                  const std::vector<RoutingEngine::OfflineRoutingGraphNodeId>& pathNodes,
                                                                                  const Eegeo::Routes::Webservice::TransportationMode& transportationMode,
                                                                                  double& out_distance,
                                                                                  double& out_duration);

                const RoutingEngine::IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;
            };
        }
    }
}
