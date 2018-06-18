// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetRouteUpdateHandler.h"
#include "RoutingQueryOptions.h"
#include "NavRoutingRouteModel.h"
#include "IAlertBoxFactory.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"

#include <string>
#include <sstream>
#include <algorithm>
#include "NavRouteInstructionHelper.h"
#include "NavRouteInteriorModelHelper.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
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

                std::string GetReadableFloorName(Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                 const std::string& indoorMapId,
                                                 const int indoorMapFloorId,
                                                 bool& out_isPlaceholder)
                {
                    std::string floorName;
                    if(NavRouteInteriorModelHelper::TryGetIndoorMapFloorName(interiorsModelRepository, indoorMapId, indoorMapFloorId, floorName))
                    {
                        out_isPlaceholder = false;
                    }
                    else
                    {
                        out_isPlaceholder = true;
                        std::ostringstream oss;
                        oss << indoorMapFloorId;
                        floorName = oss.str();
                    }
                    
                    return floorName;
                }

                std::vector<SdkModel::NavRoutingDirectionModel> GetDirectionsFromRouteData(const Eegeo::Routes::Webservice::RouteData& route,
                                                                                           Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository)
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
                            const auto& instruction = hasLocationName
                                                      ? formattedInstructions.GetInstructionLocation()
                                                      : formattedInstructions.GetShortInstructionName();
                            const auto& nextInstruction =  hasLocationName
                                                           ? formattedInstructions.GetInstructionDirection()
                                                           : std::string();

                            if (step.IsIndoors)
                            {
                                bool isUsingPlaceHolder = true;
                                std::string floorName = GetReadableFloorName(interiorsModelRepository,
                                                                             step.IndoorId,
                                                                             step.IndoorFloorId,
                                                                             isUsingPlaceHolder);

                                std::string nextFloorName;
                                
                                if (formattedInstructions.GetIsMultiFloor())
                                {
                                    nextFloorName = GetReadableFloorName(interiorsModelRepository,
                                                                         step.IndoorId,
                                                                         formattedInstructions.GetNextFloorId(),
                                                                         isUsingPlaceHolder);
                                }

                                directionsVector.emplace_back(formattedInstructions.GetShortInstructionName(),
                                                              formattedInstructions.GetIconKey(),
                                                              instruction,
                                                              nextInstruction,
                                                              step.Path,
                                                              step.Distance,
                                                              step.IsIndoors,
                                                              step.IndoorId,
                                                              step.IndoorFloorId,
                                                              floorName,
                                                              step.IsMultiFloor,
                                                              formattedInstructions.GetNextFloorId(),
                                                              nextFloorName,
                                                              isUsingPlaceHolder);
                            }
                            else
                            {
                                directionsVector.emplace_back(formattedInstructions.GetShortInstructionName(),
                                                              formattedInstructions.GetIconKey(),
                                                              instruction,
                                                              nextInstruction,
                                                              step.Path,
                                                              step.Distance);
                            }
                        }

                        sectionIndex++;
                    }

                    return directionsVector;
                }
            }
            
            NavWidgetRouteUpdateHandler::NavWidgetRouteUpdateHandler(INavRoutingModel& navRoutingModel,
                                                                     INavRoutingServiceController& navRoutingServiceController,
                                                                     Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                     Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                    : m_navRoutingModel(navRoutingModel)
                    , m_navRoutingServiceController(navRoutingServiceController)
                    , m_interiorsModelRepository(interiorsModelRepository)
                    , m_alertBoxFactory(alertBoxFactory)
                    , m_messageBus(messageBus)
                    , m_startLocation("", Eegeo::Space::LatLong(0,0))
                    , m_startLocationIsSet(false)
                    , m_endLocation("", Eegeo::Space::LatLong(0,0))
                    , m_endLocationIsSet(false)
                    , m_startLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationSet)
                    , m_startLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnStartLocationCleared)
                    , m_endLocationSetCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationSet)
                    , m_endLocationClearedCallback(this, &NavWidgetRouteUpdateHandler::OnEndLocationCleared)
                    , m_queryCompletedCallback(this, &NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted)
                    , m_queryFailedCallback(this, &NavWidgetRouteUpdateHandler::OnRoutingQueryFailed)
                    , m_failAlertHandler(this, &NavWidgetRouteUpdateHandler::OnFailAlertBoxDismissed)
                    , m_interiorModelAddedCallback(this, &NavWidgetRouteUpdateHandler::OnInteriorModelAdded)
                    , m_viewClosedMessageHandler(this, &NavWidgetRouteUpdateHandler::OnNavRoutingViewClosedMessage)
            {
                m_navRoutingModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_navRoutingModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_navRoutingModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_navRoutingModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_navRoutingServiceController.RegisterQueryCompletedCallback(m_queryCompletedCallback);
                m_navRoutingServiceController.RegisterQueryFailedCallback(m_queryFailedCallback);
                m_interiorsModelRepository.RegisterAddedCallback(m_interiorModelAddedCallback);
                m_messageBus.SubscribeNative(m_viewClosedMessageHandler);
            }

            NavWidgetRouteUpdateHandler::~NavWidgetRouteUpdateHandler()
            {
                m_messageBus.UnsubscribeNative(m_viewClosedMessageHandler);
                m_interiorsModelRepository.UnregisterAddedCallback(m_interiorModelAddedCallback);
                m_navRoutingServiceController.UnregisterQueryFailedCallback(m_queryFailedCallback);
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
                    m_navRoutingModel.ClearRoute();
                    
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
                                                                GetDirectionsFromRouteData(route, m_interiorsModelRepository),
                                                                route));
            }

            void NavWidgetRouteUpdateHandler::OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& data)
            {
                //Only using first route for now
                UpdateDirectionsFromRoute(data[0]);
            }

            void NavWidgetRouteUpdateHandler::OnRoutingQueryFailed()
            {
                m_navRoutingModel.ClearRoute();
                m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to find route",
                                                             "We couldn't find a route between those two points",
                                                             m_failAlertHandler);
            }

            void NavWidgetRouteUpdateHandler::OnFailAlertBoxDismissed()
            {
            }

            void NavWidgetRouteUpdateHandler::OnInteriorModelAdded(Eegeo::Resources::Interiors::InteriorsModel& interiorsModel)
            {
                NavRoutingRouteModel routeModel;
                if (m_navRoutingModel.TryGetRoute(routeModel))
                {
                    auto& directions = routeModel.GetDirections();
                    bool routeIsUpdated = false;

                    for (int i=0; i<directions.size(); i++)
                    {
                        auto direction = directions[i];

                        if(direction.GetIndoorMapId() == interiorsModel.GetId() && direction.GetIsIndoors() && direction.GetIsUsingPlaceHolders())
                        {
                            bool directionUpdated = false;
                            std::string floorName;
                            if (NavRouteInteriorModelHelper::TryGetIndoorMapFloorName(interiorsModel, direction.GetIndoorMapFloorId(), floorName))
                            {
                                direction.SetIndoorMapFloorName(floorName);
                                directionUpdated = true;
                            }
                            
                            std::string nextFloorName;
                            if (NavRouteInteriorModelHelper::TryGetIndoorMapFloorName(interiorsModel, direction.GetNextIndoorMapFloorId(), nextFloorName))
                            {
                                direction.SetNextIndoorMapFloorName(nextFloorName);
                                directionUpdated = true;
                            }
                            
                            if (directionUpdated)
                            {
                                direction.SetIsUsingPlaceHolders(false);
                                m_navRoutingModel.UpdateDirection(i, direction);
                                routeIsUpdated = true;
                            }
                        }
                    }

                    if (routeIsUpdated)
                    {
                        m_navRoutingModel.RouteUpdated();
                    }
                }
            }

            void NavWidgetRouteUpdateHandler::OnNavRoutingViewClosedMessage(const NavRoutingViewClosedMessage& message)
            {
                m_navRoutingServiceController.CancelRoutingQuery();
            }
        }
    }
}
