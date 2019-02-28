// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingServiceRouteDataBuilder.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingFindPathResult.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "LatLongAltitude.h"
#include "VectorMath.h"
#include "RouteData.h"
#include "MathFunc.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace
            {
                const std::string DIRECTION_TYPE_DEPART = "depart";
                const std::string DIRECTION_TYPE_ARRIVE = "arrive";

                const double WALKING_SPEED_IN_METER_PER_SECOND = 1.4;
                const double DRIVING_SPEED_IN_METER_PER_SECOND = 10;

                double GetSpeedForTransportationMode(Eegeo::Routes::Webservice::TransportationMode transportationMode)
                {
                    switch (transportationMode)
                    {
                        case Eegeo::Routes::Webservice::TransportationMode::Driving:
                            return DRIVING_SPEED_IN_METER_PER_SECOND;
                        default:
                            return WALKING_SPEED_IN_METER_PER_SECOND;
                    }
                }

                Eegeo::Space::LatLong GetLatLongFromEcef(const Eegeo::dv3& ecefPoint)
                {
                    return Eegeo::Space::LatLong::FromECEF(ecefPoint);
                }

                float Distance(const Eegeo::dv3& a, const Eegeo::dv3& b)
                {
                    return Eegeo::Math::Sqrtf(static_cast<float>(a.SquareDistanceTo(b)));
                }

                float IsPointZero(const Eegeo::dv3& point)
                {
                    return point.x == 0 && point.y == 0 && point.z == 0;
                }
            }

            OfflineRoutingServiceRouteDataBuilder::OfflineRoutingServiceRouteDataBuilder(RoutingEngine::IOfflineRoutingDataRepository& offlineRoutingDataRepository)
            : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
            {}

            std::vector<Eegeo::Routes::Webservice::RouteData> OfflineRoutingServiceRouteDataBuilder::BuildRouteData(const std::vector<RoutingEngine::OfflineRoutingFindPathResult>& pathResults,
                                                                                                                    const Eegeo::Routes::Webservice::TransportationMode& transportationMode)
            {
                const double speed = GetSpeedForTransportationMode(transportationMode);
                std::vector<Eegeo::Routes::Webservice::RouteData> routeDataVector;
                double distance = 0;
                std::vector<Eegeo::Routes::Webservice::RouteSection> sections;
                sections.reserve(pathResults.size());

                for (const auto& pathResult : pathResults)
                {
                    distance += pathResult.GetPathDistance();

                    Eegeo::Routes::Webservice::RouteSection section = { GetRouteSteps(pathResult.GetStartPoint(),
                                                                                      pathResult.GetEndPoint(),
                                                                                      pathResult.GetPathNodes(),
                                                                                      transportationMode),
                                                                        pathResult.GetPathDistance() / speed,
                                                                        pathResult.GetPathDistance() };
                    sections.push_back(section);
                }


                //We only need one route data as we only return one path per query instead of multiple path like the routing service
                Eegeo::Routes::Webservice::RouteData routeData = {sections, distance / speed, distance};
                routeDataVector.push_back(routeData);
                return routeDataVector;
            }


            std::vector<Eegeo::Routes::Webservice::RouteStep> OfflineRoutingServiceRouteDataBuilder::GetRouteSteps(const RoutingEngine::OfflineRoutingPointOnGraph& startPoint,
                                                                                                                   const RoutingEngine::OfflineRoutingPointOnGraph& endPoint,
                                                                                                                   const std::vector<RoutingEngine::OfflineRoutingGraphNodeId>& pathNodes,
                                                                                                                   const Eegeo::Routes::Webservice::TransportationMode& transportationMode)
            {
                const double speed = GetSpeedForTransportationMode(transportationMode);
                std::vector<Eegeo::Routes::Webservice::RouteStep> routeSteps;

                size_t graphPathIterator = 0;

                //Start step
                std::vector<Eegeo::Space::LatLong> startPath;
                double stepDistance = 0;
                double bearingBefore = 0;
                double bearingAfter = 0;

                Eegeo::dv3 previousPoint = Eegeo::dv3::Zero();

                if (!startPoint.GetIsPositionedOnNode())
                {
                    const auto& ecefPoint = startPoint.GetPoint();
                    startPath.push_back(GetLatLongFromEcef(ecefPoint));
                    previousPoint = ecefPoint;
                }

                const auto& startNode = m_offlineRoutingDataRepository.GetGraphNode(pathNodes.at(graphPathIterator));
                const auto& startFeature = m_offlineRoutingDataRepository.GetFeature(startNode.GetFeatureId());

                while (graphPathIterator < pathNodes.size())
                {
                    const auto& graphNode = m_offlineRoutingDataRepository.GetGraphNode(pathNodes.at(graphPathIterator));

                    if (!IsPointZero(previousPoint))
                    {
                        auto distance = Distance(previousPoint, graphNode.GetPoint());
                        stepDistance += distance;

                        if (distance > RoutingEngine::MinimumDistanceInMeters)
                        {
                            startPath.push_back(GetLatLongFromEcef(graphNode.GetPoint()));
                        }
                    }

                    //TODO turn?

                    previousPoint = graphNode.GetPoint();
                    graphPathIterator++;
                }

                Eegeo::Routes::Webservice::RouteDirections startDirections = {
                        GetLatLongFromEcef(startPoint.GetPoint()),
                        DIRECTION_TYPE_DEPART,
                        "",
                        bearingBefore,
                        bearingAfter,
                };

                Eegeo::Routes::Webservice::RouteStep startStep = { startPath,
                                                                   transportationMode,
                                                                   startPoint.GetInteriorId().Value(),
                                                                   startFeature.GetName(),
                                                                   startDirections,
                                                                   stepDistance / speed,
                                                                   stepDistance,
                                                                   startPoint.GetFloorId(),
                                                                   true,
                                                                   false };
                routeSteps.push_back(startStep);

                Eegeo::Routes::Webservice::RouteDirections endDirections = {
                        GetLatLongFromEcef(endPoint.GetPoint()),
                        DIRECTION_TYPE_ARRIVE,
                        "",
                        bearingBefore,
                        bearingAfter,
                };

                const auto& endNode = m_offlineRoutingDataRepository.GetGraphNode(pathNodes.back());
                const auto& endFeature = m_offlineRoutingDataRepository.GetFeature(endNode.GetFeatureId());

                std::vector<Eegeo::Space::LatLong> endPath;
                endPath.push_back(GetLatLongFromEcef(endPoint.GetPoint()));
                Eegeo::Routes::Webservice::RouteStep endStep = { endPath,
                                                                 transportationMode,
                                                                 endPoint.GetInteriorId().Value(),
                                                                 endFeature.GetName(),
                                                                 endDirections,
                                                                 0,
                                                                 0,
                                                                 endPoint.GetFloorId(),
                                                                 true,
                                                                 false };
                routeSteps.push_back(endStep);

                return routeSteps;
            }
        }
    }
}
