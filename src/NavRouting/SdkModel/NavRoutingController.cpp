// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingController.h"
#include "NavRoutingViewOpenMessage.h"
#include "SearchResultModel.h"
#include "NavRoutingStartLocationSetMessage.h"
#include "NavRoutingStartLocationClearedMessage.h"
#include "NavRoutingEndLocationSetMessage.h"
#include "NavRoutingEndLocationClearedMessage.h"
#include "NavRoutingRouteChangedMessage.h"
#include "NavRoutingRouteClearedMessage.h"
#include "NavRoutingCurrentDirectionSetMessage.h"
#include "NavRoutingCurrentDirectionUpdatedMessage.h"
#include "NavRoutingSelectedDirectionSetMessage.h"
#include "NavRoutingRemainingRouteDurationSetMessage.h"
#include "NavRoutingModeSetMessage.h"
#include "INavTurnByTurnModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IAlertBoxFactory.h"
#include "IWorldPinsService.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingController::NavRoutingController(INavRoutingModel& routingModel,
                                                       Eegeo::Location::ILocationService& locationService,
                                                       TurnByTurn::INavTurnByTurnModel& turnByTurnModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                       Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                       Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService)
            : m_routingModel(routingModel)
            , m_locationService(locationService)
            , m_turnByTurnModel(turnByTurnModel)
            , m_messageBus(messageBus)
            , m_interiorsModelRepository(interiorsModelRepository)
            , m_alertBoxFactory(alertBoxFactory)
            , m_worldPinsService(worldPinsService)
            , m_isRerouting(false)
            , m_startLocationSetCallback(this, &NavRoutingController::OnStartLocationSet)
            , m_startLocationClearedCallback(this, &NavRoutingController::OnStartLocationCleared)
            , m_endLocationSetCallback(this, &NavRoutingController::OnEndLocationSet)
            , m_endLocationClearedCallback(this, &NavRoutingController::OnEndLocationCleared)
            , m_routeSetCallback(this, &NavRoutingController::OnRouteSet)
            , m_routeClearedCallback(this, &NavRoutingController::OnRouteCleared)
            , m_routeUpdatedCallback(this, &NavRoutingController::OnRouteUpdated)
            , m_currentDirectionSetCallback(this, &NavRoutingController::OnCurrentDirectionSet)
            , m_currentDirectionUpdatedCallback(this, &NavRoutingController::OnCurrentDirectionUpdated)
            , m_selectedDirectionSetCallback(this, &NavRoutingController::OnSelectedDirectionSet)
            , m_remainingRouteDurationSetCallback(this, &NavRoutingController::OnRemainingRouteDurationSet)
            , m_navRoutingModeSetCallback(this, &NavRoutingController::OnNavRoutingModeSet)
            , m_viewClosedMessageHandler(this, &NavRoutingController::OnNavWidgetViewClosed)
            , m_startEndLocationSwappedMessageHandler(this, &NavRoutingController::OnStartEndLocationSwapped)
            , m_startLocationClearClickedMessageHandler(this, &NavRoutingController::OnStartLocationClearClicked)
            , m_endLocationClearClickedMessageHandler(this, &NavRoutingController::OnEndLocationClearClicked)
            , m_startEndRoutingButtonClickedMessageHandler(this, &NavRoutingController::OnStartEndRoutingButtonClicked)
            , m_selectedDirectionChangedMessageHandler(this, &NavRoutingController::OnSelectedDirectionChanged)
            , m_directionsButtonClickedMessageHandler(this, &NavRoutingController::OnDirectionsButtonClicked)
            , m_failAlertHandler(this, &NavRoutingController::OnFailAlertBoxDismissed)
            , m_shouldRerouteCallback(this, &NavRoutingController::OnShouldReroute)
            {
                m_routingModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_routingModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_routingModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_routingModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_routingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_routingModel.InsertRouteClearedCallback(m_routeClearedCallback);
                m_routingModel.InsertRouteUpdatedCallback(m_routeUpdatedCallback);
                m_routingModel.InsertSelectedDirectionSetCallback(m_selectedDirectionSetCallback);
                m_routingModel.InsertCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_routingModel.InsertCurrentDirectionUpdatedCallback(m_currentDirectionUpdatedCallback);
                m_routingModel.InsertRemainingRouteDurationSetCallback(m_remainingRouteDurationSetCallback);
                m_routingModel.InsertNavModeSetCallback(m_navRoutingModeSetCallback);
                m_messageBus.SubscribeNative(m_viewClosedMessageHandler);
                m_messageBus.SubscribeNative(m_startEndLocationSwappedMessageHandler);
                m_messageBus.SubscribeNative(m_startLocationClearClickedMessageHandler);
                m_messageBus.SubscribeNative(m_endLocationClearClickedMessageHandler);
                m_messageBus.SubscribeNative(m_startEndRoutingButtonClickedMessageHandler);
                m_messageBus.SubscribeNative(m_selectedDirectionChangedMessageHandler);
                m_messageBus.SubscribeNative(m_directionsButtonClickedMessageHandler);
                m_turnByTurnModel.InsertShouldRerouteCallback(m_shouldRerouteCallback);
            }

            NavRoutingController::~NavRoutingController()
            {
                m_turnByTurnModel.RemoveShouldRerouteCallback(m_shouldRerouteCallback);
                m_messageBus.UnsubscribeNative(m_directionsButtonClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_selectedDirectionChangedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startEndRoutingButtonClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_endLocationClearClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startLocationClearClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startEndLocationSwappedMessageHandler);
                m_messageBus.UnsubscribeNative(m_viewClosedMessageHandler);
                m_routingModel.RemoveNavModeSetCallback(m_navRoutingModeSetCallback);
                m_routingModel.RemoveRemainingRouteDurationSetCallback(m_remainingRouteDurationSetCallback);
                m_routingModel.RemoveCurrentDirectionUpdatedCallback(m_currentDirectionUpdatedCallback);
                m_routingModel.RemoveCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_routingModel.RemoveSelectedDirectionSetCallback(m_selectedDirectionSetCallback);
                m_routingModel.RemoveRouteUpdatedCallback(m_routeUpdatedCallback);
                m_routingModel.RemoveRouteClearedCallback(m_routeClearedCallback);
                m_routingModel.RemoveRouteSetCallback(m_routeSetCallback);
                m_routingModel.RemoveEndLocationClearedCallback(m_endLocationClearedCallback);
                m_routingModel.RemoveEndLocationSetCallback(m_endLocationSetCallback);
                m_routingModel.RemoveStartLocationClearedCallback(m_startLocationClearedCallback);
                m_routingModel.RemoveStartLocationSetCallback(m_startLocationSetCallback);
            }

            bool NavRoutingController::TryGetCurrentLocation(NavRoutingLocationModel &location)
            {
                if(!m_locationService.GetIsAuthorized())
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Location service is not authorized",
                                                                 "We didn't recieve autorization for location service",
                                                                 m_failAlertHandler);
                    return false;
                }

                Eegeo::Space::LatLong currentLocation = Eegeo::Space::LatLong(0,0);
                if(m_locationService.GetLocation(currentLocation))
                {
                    int indoorMapFloorId = 0;
                    m_locationService.GetFloorIndex(indoorMapFloorId);

                    location = NavRoutingLocationModel("Current Location",
                                                       currentLocation,
                                                       m_locationService.IsIndoors(),
                                                       m_locationService.GetInteriorId(),
                                                       indoorMapFloorId);
                    return true;
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to acquire location",
                                                                 "We couldn't find your current location",
                                                                 m_failAlertHandler);
                    return false;
                }
            }

            void NavRoutingController::OnStartLocationSet(const NavRoutingLocationModel& startLocation)
            {
                m_messageBus.Publish(NavRoutingStartLocationSetMessage(startLocation));
            }

            void NavRoutingController::OnStartLocationCleared()
            {
                m_messageBus.Publish(NavRoutingStartLocationClearedMessage());
            }

            void NavRoutingController::OnEndLocationSet(const NavRoutingLocationModel& endLocation)
            {
                m_messageBus.Publish(NavRoutingEndLocationSetMessage(endLocation));
            }

            void NavRoutingController::OnEndLocationCleared()
            {
                m_messageBus.Publish(NavRoutingEndLocationClearedMessage());
            }

            void NavRoutingController::OnRouteSet(const NavRoutingRouteModel& routeModel)
            {
                m_messageBus.Publish(NavRoutingRouteChangedMessage(routeModel, true));
                if (m_isRerouting)
                {
                    m_turnByTurnModel.Start(routeModel.GetSourceRouteData());
                    m_isRerouting = false;
                }
                else
                {
                    m_routingModel.SetNavMode(Ready);
                }
                m_routingModel.SetRemainingRouteDuration(routeModel.GetDuration());
                m_worldPinsService.DeselectPin();
            }

            void NavRoutingController::OnRouteCleared()
            {
                m_messageBus.Publish(NavRoutingRouteClearedMessage());
                m_routingModel.SetNavMode(NotReady);
                m_routingModel.SetRemainingRouteDuration(0);
            }

            void NavRoutingController::OnRouteUpdated(const NavRoutingRouteModel& routeModel)
            {
                m_messageBus.Publish(NavRoutingRouteChangedMessage(routeModel, false));
            }

            void NavRoutingController::OnCurrentDirectionSet(const int& directionIndex)
            {
                m_messageBus.Publish(NavRoutingCurrentDirectionSetMessage(directionIndex));
            }

            void NavRoutingController::OnCurrentDirectionUpdated(const NavRoutingDirectionModel& directionModel)
            {
                m_messageBus.Publish(NavRoutingCurrentDirectionUpdatedMessage(directionModel));
            }

            void NavRoutingController::OnSelectedDirectionSet(const int& directionIndex)
            {
                m_messageBus.Publish(NavRoutingSelectedDirectionSetMessage(directionIndex));
            }

            void NavRoutingController::OnRemainingRouteDurationSet(const double& seconds)
            {
                m_messageBus.Publish(NavRoutingRemainingRouteDurationSetMessage(seconds));
            }

            void NavRoutingController::OnNavRoutingModeSet(const NavRoutingMode& mode)
            {
                m_messageBus.Publish(NavRoutingModeSetMessage(mode));
            }

            void NavRoutingController::OnNavWidgetViewClosed(const NavRoutingViewClosedMessage& message)
            {
                m_routingModel.ClearRoute();
            }

            void NavRoutingController::OnStartEndLocationSwapped(const NavRoutingViewStartEndLocationSwappedMessage& message)
            {
                NavRoutingLocationModel startLocation, endLocation;

                m_routingModel.TryGetStartLocation(startLocation);
                m_routingModel.TryGetEndLocation(endLocation);

                NavRoutingLocationModel tempLocation = startLocation;
                startLocation = endLocation;
                endLocation = tempLocation;

                m_routingModel.SetStartLocation(startLocation);
                m_routingModel.SetEndLocation(endLocation);

                m_routingModel.ClearRoute();
            }

            void NavRoutingController::OnStartLocationClearClicked(const NavRoutingStartLocationClearClickedMessage& message)
            {
                m_routingModel.ClearStartLocation();
            }

            void NavRoutingController::OnEndLocationClearClicked(const NavRoutingEndLocationClearClickedMessage& message)
            {
                m_routingModel.ClearEndLocation();
            }

            void NavRoutingController::OnStartEndRoutingButtonClicked(const NavRoutingStartEndRoutingButtonClickedMessage& message)
            {
                switch (m_routingModel.GetNavMode())
                {
                    case NavRoutingMode::Active:
                        m_turnByTurnModel.Stop();
                        break;
                    case NavRoutingMode::Ready:
                    {
                        NavRoutingRouteModel routeModel;
                        if(m_routingModel.TryGetRoute(routeModel))
                        {
                            m_turnByTurnModel.Start(routeModel.GetSourceRouteData());
                        }
                        else
                        {
                            m_routingModel.SetNavMode(NavRoutingMode::NotReady);
                        }
                        break;
                    }
                    default:
                        m_routingModel.SetNavMode(NavRoutingMode::NotReady);
                        break;
                }
            }

            void NavRoutingController::OnSelectedDirectionChanged(const NavRoutingSelectedDirectionChangedMessage& message)
            {
                m_routingModel.SetSelectedDirection(message.GetDirectionIndex());
            }

            void NavRoutingController::OnDirectionsButtonClicked(const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage& message)
            {
                NavRoutingLocationModel startLocation, endLocation;
                
                if (!TryGetCurrentLocation(startLocation))
                {
                    return;
                }

                const auto& searchResultModel = message.GetModel();
                
                if(searchResultModel.IsInterior())
                {
                    const auto& indoorMapId = searchResultModel.GetBuildingId().Value();
                    if (m_interiorsModelRepository.HasInterior(indoorMapId))
                    {
                        auto& interiorModel = m_interiorsModelRepository.GetInterior(indoorMapId);
                        auto& floorModel = interiorModel.GetFloorAtIndex(searchResultModel.GetFloor());
                        endLocation = NavRoutingLocationModel(searchResultModel.GetTitle(),
                                                              searchResultModel.GetLocation(),
                                                              searchResultModel.IsInterior(),
                                                              searchResultModel.GetBuildingId(),
                                                              floorModel.GetFloorNumber());
                    }
                    else
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Interior not loaded",
                                                                     "Interior information is not available",
                                                                     m_failAlertHandler);
                        return;
                    }
                }
                else
                {
                    endLocation = NavRoutingLocationModel(searchResultModel.GetTitle(),
                                                          searchResultModel.GetLocation(),
                                                          searchResultModel.IsInterior(),
                                                          searchResultModel.GetBuildingId(),
                                                          searchResultModel.GetFloor());
                }
                
                m_routingModel.SetStartLocation(startLocation);
                m_routingModel.SetEndLocation(endLocation);

                m_messageBus.Publish(NavRoutingViewOpenMessage(m_routingModel));
            }
            
            void NavRoutingController::OnFailAlertBoxDismissed()
            {
            }

            void NavRoutingController::OnShouldReroute()
            {
                NavRoutingLocationModel startLocation;

                if (TryGetCurrentLocation(startLocation))
                {
                    //TODO add ui dialog box
                    m_routingModel.SetStartLocation(startLocation);
                    m_isRerouting = true;
                    m_turnByTurnModel.Stop();
                }
            }
        }
    }
}
