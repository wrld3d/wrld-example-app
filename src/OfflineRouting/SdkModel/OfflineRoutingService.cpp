// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingService.h"
#include "IOfflineRoutingGraphPositioner.h"
#include "IOfflineRoutingPathFinder.h"
#include "OfflineRoutingPointOnGraph.h"
#include "RoutingQueryOptions.h"
#include "RoutingQueryResponse.h"
#include "OfflineRoutingFindPathResult.h"
#include "RouteData.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            bool CheckQueryPointsAreValid(const std::vector<RoutingEngine::OfflineRoutingPointOnGraph>& queryPoints)
            {
                if (queryPoints.size() < 2)
                {
                    return false;
                }

                const auto& interiorId = queryPoints.front().GetInteriorId();

                for (size_t i = 1; i < queryPoints.size(); i++)
                {
                    if (interiorId != queryPoints.at(i).GetInteriorId())
                    {
                        return false;
                    }
                }

                return true;
            }

            OfflineRoutingService::OfflineRoutingService(RoutingEngine::IOfflineRoutingGraphPositioner& offlineRoutingGraphPositioner,
                                                         RoutingEngine::IOfflineRoutingPathFinder& offlineRoutingPathFinder)
            : m_offlineRoutingGraphPositioner(offlineRoutingGraphPositioner)
            , m_offlineRoutingPathFinder(offlineRoutingPathFinder)
            {
            }

            Eegeo::Routes::Webservice::RoutingQueryId OfflineRoutingService::BeginRoutingQuery(const Eegeo::Routes::Webservice::RoutingQueryOptions& options)
            {
                Eegeo::Routes::Webservice::RoutingQueryId routingQueryId = m_routingQueryIdGenerator.GetNext();

                m_queriesToProcess.insert({routingQueryId, options});

                return routingQueryId;
            }

            void OfflineRoutingService::CancelQuery(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId)
            {
                const auto it = m_queriesToProcess.find(routingQueryId);
                if (it != m_queriesToProcess.end())
                {
                    m_queriesToProcess.erase(it);
                }
            }

            void OfflineRoutingService::RegisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback)
            {
                m_queryCompletedCallbacks.AddCallback(callback);
            }

            void OfflineRoutingService::UnregisterQueryCompletedCallback(Eegeo::Routes::Webservice::RoutingQueryCompletedCallback& callback)
            {
                m_queryCompletedCallbacks.RemoveCallback(callback);
            }

            void OfflineRoutingService::Update(float dt)
            {
                ProcessQueries();
            }

            bool OfflineRoutingService::TryFindPointsOnGraph(const std::vector<Eegeo::Routes::Webservice::RoutingQueryWaypoint>& waypoints,
                                                             std::vector<RoutingEngine::OfflineRoutingPointOnGraph>& pointsOnGraph)
            {
                pointsOnGraph.reserve(waypoints.size());

                for (const auto& waypoint: waypoints)
                {
                    const auto& pointOnGraph = m_offlineRoutingGraphPositioner.FindPointOnGraph(waypoint.LatLong, waypoint.FloorNumber, 10);

                    if (!pointOnGraph.GetIsPointValid())
                    {
                        return false;
                    }

                    pointsOnGraph.emplace_back(pointOnGraph);
                }

                return true;
            }

            bool OfflineRoutingService::TryFindPaths(const std::vector<RoutingEngine::OfflineRoutingPointOnGraph> queryPoints,
                                                     std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults)
            {
                pathResults.reserve(queryPoints.size()-1);

                for (size_t i = 0; i < queryPoints.size()-1; i++)
                {
                    const RoutingEngine::OfflineRoutingFindPathResult& result = m_offlineRoutingPathFinder.FindPath(queryPoints.at(i), queryPoints.at(i+1));

                    if (!result.GetPathFound())
                    {
                        return false;
                    }

                    pathResults.emplace_back(result);
                }
                return true;
            }

            void OfflineRoutingService::BuildRouteData(const std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults,
                                                       std::vector<Eegeo::Routes::Webservice::RouteData>& routes)
            {
                double distance = 0;
                std::vector<Eegeo::Routes::Webservice::RouteSection> sections;

                //TODO remove from here, also calculate based on transportation mode
                double speed = 1; //meter/second or meter/min? need to lookup

                for (const auto& pathResult : pathResults)
                {
                    std::vector<Eegeo::Space::LatLong> path;
                    std::string IndoorId;
                    std::string Name;

                    path.push_back(Eegeo::Space::LatLong::FromECEF(pathResult.GetStartPoint().GetPoint()));

                    std::vector<Eegeo::Routes::Webservice::RouteStep> steps;

                    Eegeo::Routes::Webservice::RouteDirections directions = {{0, 0}};

                    Eegeo::Routes::Webservice::RouteStep step = { path,
                                                                  Eegeo::Routes::Webservice::TransportationMode::Walking,
                                                                  pathResult.GetStartPoint().GetInteriorId().Value(),
                                                                  "Depart",
                                                                  directions,
                                                                  1,
                                                                  1,
                                                                  pathResult.GetStartPoint().GetFloorId(),
                                                                  true,
                                                                  false };
                    steps.push_back(step);

                    Eegeo::Routes::Webservice::RouteSection section = {steps, pathResult.GetPathDistance() / speed, pathResult.GetPathDistance()};
                    sections.push_back(section);

                    distance += pathResult.GetPathDistance();
                }

                routes.push_back({sections, distance / speed, distance});
            }

            void OfflineRoutingService::ProcessQueries()
            {
                for (const auto& query : m_queriesToProcess)
                {
                    const auto& routingQueryId = query.first;
                    const auto& options = query.second;

                    if (options.Waypoints.size() < 2)
                    {
                        NotifyQueryFailed(routingQueryId);
                        continue;
                    }

                    std::vector<RoutingEngine::OfflineRoutingPointOnGraph> queryPoints;

                    if (!TryFindPointsOnGraph(options.Waypoints, queryPoints))
                    {
                        NotifyQueryFailed(routingQueryId);
                        continue;
                    }

                    Eegeo_ASSERT(options.Waypoints.size() == queryPoints.size());

                    if (!CheckQueryPointsAreValid(queryPoints))
                    {
                        NotifyQueryFailed(routingQueryId);
                        continue;
                    }

                    std::vector<RoutingEngine::OfflineRoutingFindPathResult> pathResults;

                    if (!TryFindPaths(queryPoints, pathResults))
                    {
                        NotifyQueryFailed(routingQueryId);
                        continue;
                    }

                    Eegeo_ASSERT(pathResults.size() == (queryPoints.size()-1));

                    std::vector<Eegeo::Routes::Webservice::RouteData> routeData;
                    BuildRouteData(pathResults, routeData);

                    NotifyQuerySuccess(routingQueryId, routeData);
                }

                m_queriesToProcess.clear();
            }

            void OfflineRoutingService::NotifyQuerySuccess(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId,
                                                           const std::vector<Eegeo::Routes::Webservice::RouteData>& routeData)
            {
                Eegeo::Routes::Webservice::RoutingQueryResponse response = Eegeo::Routes::Webservice::RoutingQueryResponse(routingQueryId,
                                                                                                                           true,
                                                                                                                           routeData);
                m_queryCompletedCallbacks.ExecuteCallbacks(response);
            }

            void OfflineRoutingService::NotifyQueryFailed(Eegeo::Routes::Webservice::RoutingQueryId routingQueryId)
            {
                std::vector<Eegeo::Routes::Webservice::RouteData> routeData;
                Eegeo::Routes::Webservice::RoutingQueryResponse response = Eegeo::Routes::Webservice::RoutingQueryResponse(routingQueryId,
                                                                                                                           false,
                                                                                                                           routeData);
                m_queryCompletedCallbacks.ExecuteCallbacks(response);
            }
        }
    }
}
