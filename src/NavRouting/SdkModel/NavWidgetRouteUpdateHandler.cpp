// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteUpdateHandler.h"
#include "RoutingQueryOptions.h"
#include "NavRoutingRouteModel.h"

#include <string>
#include <sstream>
#include <algorithm>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            Eegeo::Routes::Webservice::RoutingQueryWaypoint GetWaypoint(const NavRoutingLocationModel& locationModel)
            {

                return Eegeo::Routes::Webservice::RoutingQueryWaypoint
                        {
                               locationModel.GetLatLon(),
                               locationModel.GetIsIndoors(),
                               locationModel.GetIndoorMapFloorId()
                       };
            }

            std::string GetIconNameFromType(const std::string& directionType, const std::string& directionModifier)
            {
                std::string type = directionType;
                std::string modifier = directionModifier;

                std::replace(type.begin(), type.end(), ' ', '_');
                std::replace(modifier.begin(), modifier.end(), ' ', '_');

                if(type == "arrive")
                {
                    return "finish";
                }
                else if(type == "depart")
                {
                    return "start";
                }

                if (type == "new_name")
                {
                    type = "turn";
                }

                if(type == "turn" && modifier == "straight")
                {
                    return "straight_ahead";
                }

                return (type + "_" + modifier);
            }

            std::string GetCurrentInstructionFromType(const std::string& directionType, const std::string& directionModifier, bool shouldCapitalize = true)
            {
                std::string type = directionType;
                std::string modifier = directionModifier;

                if (type == "new name")
                {
                    type = "turn";
                }

                if (type == "turn" && modifier == "straight")
                {
                    return ((shouldCapitalize ? "Continue " : "continue ") + modifier);
                }

                if (type == "turn" && modifier == "uturn")
                {
                    return ((shouldCapitalize ? "Make a U-turn" : "make a U-turn") + modifier);
                }

                if (shouldCapitalize)
                {
                    type[0] = (char) toupper(type[0]);
                }

                return (type + " " + modifier);
            }

            std::vector<NavRoutingDirectionModel> GetDirectionsFromRouteData(const Eegeo::Routes::Webservice::RouteData& route)
            {
                std::vector<NavRoutingDirectionModel> directionsVector;

                for (auto& section: route.Sections)
                {
                    int count = static_cast<int>(section.Steps.size());
                    for (int i=0; i<count; i++)
                    {
                        auto& step = section.Steps[i];
                        auto& directions = step.Directions;

                        std::string name = GetCurrentInstructionFromType(directions.Type, directions.Modifier);
                        std::ostringstream directionStringStream;
                        directionStringStream << (int) step.Distance << "m - " << name;
                        std::string currentInstruction = directionStringStream.str();
                        std::string nextInstruction = "Arrived at destination.";

                        if ((i+1)<count)
                        {
                            auto& nextStep = section.Steps[i+1];
                            auto& nextDirection = nextStep.Directions;

                            nextInstruction = "Then " + GetCurrentInstructionFromType(nextDirection.Type, nextDirection.Modifier, false);
                        }

                        directionsVector.emplace_back(currentInstruction,
                                                      GetIconNameFromType(directions.Type, directions.Modifier),
                                                      currentInstruction,
                                                      nextInstruction,
                                                      step.Path,
                                                      step.IsIndoors,
                                                      step.IndoorId,
                                                      step.IndoorFloorId,
                                                      step.IsMultiFloor);
                    }
                }

                return directionsVector;
            }

            NavWidgetRouteUpdateHandler::NavWidgetRouteUpdateHandler(INavRoutingModel& navRoutingModel,
                                                                     INavRoutingServiceController& navRoutingServiceController)
                    : m_navRoutingModel(navRoutingModel)
                    , m_navRoutingServiceController(navRoutingServiceController)
                    , m_startLocation("", Eegeo::Space::LatLong(0,0))
                    , m_startLocationIsSet(false)
                    , m_endLocation("", Eegeo::Space::LatLong(0,0))
                    , m_endLocationIsSet(false)
                    , m_startLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationSet)
                    , m_startLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationCleared)
                    , m_endLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationSet)
                    , m_endLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationCleared)
                    , m_queryCompletedCallback(this, &NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted)
            {
                m_navRoutingModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_navRoutingModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navRoutingModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_navRoutingModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_navRoutingServiceController.RegisterQueryCompletedCallback(m_queryCompletedCallback);
            }

            NavWidgetRouteUpdateHandler::~NavWidgetRouteUpdateHandler()
            {
                m_navRoutingServiceController.UnregisterQueryCompletedCallback(m_queryCompletedCallback);
                m_navRoutingModel.RemoveEndLocationClearedCallback(m_endLocationClearedCallback);
                m_navRoutingModel.RemoveEndLocationSetCallback(m_endLocationSetCallback);
                m_navRoutingModel.RemoveStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navRoutingModel.RemoveStartLocationSetCallback(m_startLocationSetCallback);
            }

            void NavWidgetRouteUpdateHandler::OnStartLocationSet(const NavRoutingLocationModel& startLocation)
            {
                m_startLocation = startLocation;
                m_startLocationIsSet = true;

                UpdateRoute();
            }

            void NavWidgetRouteUpdateHandler::OnStartLocationCleared()
            {
                m_startLocationIsSet = false;

                m_navRoutingModel.ClearRoute();
            }

            void NavWidgetRouteUpdateHandler::OnEndLocationSet(const NavRoutingLocationModel& endLocation)
            {
                m_endLocation = endLocation;
                m_endLocationIsSet = true;

                UpdateRoute();
            }

            void NavWidgetRouteUpdateHandler::OnEndLocationCleared()
            {
                m_endLocationIsSet = false;

                m_navRoutingModel.ClearRoute();
            }

            void NavWidgetRouteUpdateHandler::UpdateRoute()
            {
                if (m_startLocationIsSet && m_endLocationIsSet)
                {
                    std::vector<Eegeo::Routes::Webservice::RoutingQueryWaypoint> waypoints;
                    waypoints.reserve(2);

                    waypoints.emplace_back(GetWaypoint(m_startLocation));
                    waypoints.emplace_back(GetWaypoint(m_endLocation));

                    Eegeo::Routes::Webservice::RoutingQueryOptions queryOptions(waypoints);
                    m_navRoutingServiceController.MakeRoutingQuery(queryOptions);
                }
            }

            void NavWidgetRouteUpdateHandler::UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route)
            {
                m_navRoutingModel.SetRoute(NavRoutingRouteModel(route.Duration,
                                                                route.Distance,
                                                                GetDirectionsFromRouteData(route)));
            }

            void NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& data)
            {
                //Only using first route for now
                UpdateDirectionsFromRoute(data[0]);
            }
        }
    }
}
