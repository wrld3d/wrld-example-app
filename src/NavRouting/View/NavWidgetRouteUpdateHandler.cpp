// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteUpdateHandler.h"
#include "RoutingQueryOptions.h"
#include "NavRoutingRouteModel.h"
#include "NavRoutingViewPerformedRouteQueryMessage.h"

#include <string>
#include <sstream>
#include <algorithm>
#include "NavRouteInstructionHelper.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            namespace
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

                std::vector<SdkModel::NavRoutingDirectionModel> GetDirectionsFromRouteData(const Eegeo::Routes::Webservice::RouteData& route)
                {
                    std::vector<SdkModel::NavRoutingDirectionModel> directionsVector;

                    int sectionIndex = 0;
                    for (auto& section: route.Sections)
                    {
                        int count = static_cast<int>(section.Steps.size());
                        for (int i=0; i<count; i++)
                        {
                            auto& step = section.Steps[i];

                            SdkModel::NavRouteFormattedInstructions formattedInstructions = SdkModel::NavRouteInstructionHelper::GetFormattedInstructionForStep(
                                    route, sectionIndex, i);

                            bool hasLocationName = !formattedInstructions.GetInstructionLocation().empty();
                            directionsVector.emplace_back(formattedInstructions.GetShortInstructionName(),
                                                          formattedInstructions.GetIconKey(),
                                                          hasLocationName ? formattedInstructions.GetInstructionLocation() : formattedInstructions.GetShortInstructionName(),
                                                          hasLocationName ? formattedInstructions.GetInstructionDirection() : std::string(),
                                                          step.Path,
                                                          step.IsIndoors,
                                                          step.IndoorId,
                                                          step.IndoorFloorId,
                                                          step.IsMultiFloor);
                        }

                        sectionIndex++;
                    }

                    return directionsVector;
                }
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
                    , m_startEndLocationSwappedMessageHandler(this, &NavWidgetRouteUpdateHandler::OnStartEndLocationSwapped)
            {
                m_navWidgetViewModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_navWidgetViewModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navWidgetViewModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_navWidgetViewModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_messageBus.SubscribeUi(m_queryCompletedMessageHandler);
                m_messageBus.SubscribeNative(m_startEndLocationSwappedMessageHandler);
            }

            NavWidgetRouteUpdateHandler::~NavWidgetRouteUpdateHandler()
            {
                m_messageBus.UnsubscribeNative(m_startEndLocationSwappedMessageHandler);
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

            void NavWidgetRouteUpdateHandler::OnStartEndLocationSwapped(const NavRoutingViewStartEndLocationSwappedMessage& message)
            {
                SdkModel::NavRoutingLocationModel tempLocation = m_startLocation;
                m_startLocation = m_endLocation;
                m_endLocation = tempLocation;

                UpdateRoute();
            }
        }
    }
}
