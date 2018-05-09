// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteUpdateHandler.h"
#include "RoutingQueryOptions.h"
#include "NavRoutingRouteModel.h"
#include "NavRoutingViewPerformedRouteQueryMessage.h"

#include <string>
#include <sstream>
#include <algorithm>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            Eegeo::Routes::Webservice::RoutingQueryWaypoint GetWaypoint(const SdkModel::NavRoutingLocationModel& locationModel)
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

                if (type == "arrive" || type == "depart")
                {
                    return type;
                }

                if (type == "new_name")
                {
                    type = "turn";
                }

                if (type == "turn" && modifier == "straight")
                {
                    return modifier;
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

            std::vector<SdkModel::NavRoutingDirectionModel> GetDirectionsFromRouteData(const Eegeo::Routes::Webservice::RouteData& route)
            {
                std::vector<SdkModel::NavRoutingDirectionModel> directionsVector;

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

            NavWidgetRouteUpdateHandler::NavWidgetRouteUpdateHandler(INavWidgetViewModel& navWidgetViewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                    : m_navWidgetViewModel(navWidgetViewModel)
                    , m_messageBus(messageBus)
                    , m_startLocation("", Eegeo::Space::LatLong(0,0))
                    , m_startLocationIsSet(false)
                    , m_endLocation("", Eegeo::Space::LatLong(0,0))
                    , m_endLocationIsSet(false)
                    , m_startLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationSet)
                    , m_startLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationCleared)
                    , m_endLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationSet)
                    , m_endLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationCleared)
                    , m_queryCompletedMessageHandler(this, &NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted)
            {
                m_navWidgetViewModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_navWidgetViewModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navWidgetViewModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_navWidgetViewModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_messageBus.SubscribeUi(m_queryCompletedMessageHandler);
            }

            NavWidgetRouteUpdateHandler::~NavWidgetRouteUpdateHandler()
            {
                m_messageBus.UnsubscribeUi(m_queryCompletedMessageHandler);
                m_navWidgetViewModel.RemoveEndLocationClearedCallback(m_endLocationClearedCallback);
                m_navWidgetViewModel.RemoveEndLocationSetCallback(m_endLocationSetCallback);
                m_navWidgetViewModel.RemoveStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navWidgetViewModel.RemoveStartLocationSetCallback(m_startLocationSetCallback);
            }

            void NavWidgetRouteUpdateHandler::OnStartLocationSet(const SdkModel::NavRoutingLocationModel& startLocation)
            {
                m_startLocation = startLocation;
                m_startLocationIsSet = true;

                UpdateRoute();
            }

            void NavWidgetRouteUpdateHandler::OnStartLocationCleared()
            {
                m_startLocationIsSet = false;

                m_navWidgetViewModel.ClearRoute();
            }

            void NavWidgetRouteUpdateHandler::OnEndLocationSet(const SdkModel::NavRoutingLocationModel& endLocation)
            {
                m_endLocation = endLocation;
                m_endLocationIsSet = true;

                UpdateRoute();
            }

            void NavWidgetRouteUpdateHandler::OnEndLocationCleared()
            {
                m_endLocationIsSet = false;

                m_navWidgetViewModel.ClearRoute();
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
                    m_messageBus.Publish(NavRoutingViewPerformedRouteQueryMessage(queryOptions));
                }
            }

            void NavWidgetRouteUpdateHandler::UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route)
            {
                m_navWidgetViewModel.SetRoute(SdkModel::NavRoutingRouteModel(route.Duration,
                                                                             route.Distance,
                                                                             GetDirectionsFromRouteData(route)));
            }

            void NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted(const NavRoutingQueryCompletedMessage& message)
            {
                //Only using first route for now
                UpdateDirectionsFromRoute(message.GetRouteData()[0]);
            }
        }
    }
}
