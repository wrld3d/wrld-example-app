// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingController.h"
#include "NavRoutingViewOpenMessage.h"
#include "SearchResultModel.h"
#include "NavRoutingStartLocationSetMessage.h"
#include "NavRoutingStartLocationClearedMessage.h"
#include "NavRoutingEndLocationSetMessage.h"
#include "NavRoutingEndLocationClearedMessage.h"
#include "NavRoutingRouteSetMessage.h"
#include "NavRoutingRouteClearedMessage.h"
#include "NavRoutingCurrentDirectionSetMessage.h"
#include "NavRoutingRemainingRouteDurationSetMessage.h"
#include "NavRoutingModeSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingController::NavRoutingController(INavRoutingModel& routingModel,
                                                       Eegeo::Location::ILocationService& locationService,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : m_routingModel(routingModel)
            , m_locationService(locationService)
            , m_messageBus(messageBus)
            , m_startLocationSetCallback(this, &NavRoutingController::OnStartLocationSet)
            , m_startLocationClearedCallback(this, &NavRoutingController::OnStartLocationCleared)
            , m_endLocationSetCallback(this, &NavRoutingController::OnEndLocationSet)
            , m_endLocationClearedCallback(this, &NavRoutingController::OnEndLocationCleared)
            , m_routeSetCallback(this, &NavRoutingController::OnRouteSet)
            , m_routeClearedCallback(this, &NavRoutingController::OnRouteCleared)
            , m_currentDirectionSetCallback(this, &NavRoutingController::OnCurrentDirectionSet)
            , m_remainingRouteDurationSetCallback(this, &NavRoutingController::OnRemainingRouteDurationSet)
            , m_navRoutingModeSetCallback(this, &NavRoutingController::OnNavRoutingModeSet)
            , m_viewClosedMessageHandler(this, &NavRoutingController::OnNavWidgetViewClosed)
            , m_startEndLocationSwappedMessageHandler(this, &NavRoutingController::OnStartEndLocationSwapped)
            , m_startLocationClearClickedMessageHandler(this, &NavRoutingController::OnStartLocationClearClicked)
            , m_endLocationClearClickedMessageHandler(this, &NavRoutingController::OnEndLocationClearClicked)
            , m_startEndRoutingButtonClickedMessageHandler(this, &NavRoutingController::OnStartEndRoutingButtonClicked)
            , m_selectedDirectionChangedMessageHandler(this, &NavRoutingController::OnSelectedDirectionChanged)
            , m_directionsButtonClickedMessageHandler(this, &NavRoutingController::OnDirectionsButtonClicked)
            {
                m_routingModel.InsertStartLocationSetCallback(m_startLocationSetCallback);
                m_routingModel.InsertStartLocationClearedCallback(m_startLocationClearedCallback);
                m_routingModel.InsertEndLocationSetCallback(m_endLocationSetCallback);
                m_routingModel.InsertEndLocationClearedCallback(m_endLocationClearedCallback);
                m_routingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_routingModel.InsertRouteClearedCallback(m_routeClearedCallback);
                m_routingModel.InsertCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_routingModel.InsertRemainingRouteDurationSetCallback(m_remainingRouteDurationSetCallback);
                m_routingModel.InsertNavModeSetCallback(m_navRoutingModeSetCallback);
                m_messageBus.SubscribeNative(m_viewClosedMessageHandler);
                m_messageBus.SubscribeNative(m_startEndLocationSwappedMessageHandler);
                m_messageBus.SubscribeNative(m_startLocationClearClickedMessageHandler);
                m_messageBus.SubscribeNative(m_endLocationClearClickedMessageHandler);
                m_messageBus.SubscribeNative(m_startEndRoutingButtonClickedMessageHandler);
                m_messageBus.SubscribeNative(m_selectedDirectionChangedMessageHandler);
                m_messageBus.SubscribeNative(m_directionsButtonClickedMessageHandler);
            }

            NavRoutingController::~NavRoutingController()
            {
                m_messageBus.UnsubscribeNative(m_directionsButtonClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_selectedDirectionChangedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startEndRoutingButtonClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_endLocationClearClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startLocationClearClickedMessageHandler);
                m_messageBus.UnsubscribeNative(m_startEndLocationSwappedMessageHandler);
                m_messageBus.UnsubscribeNative(m_viewClosedMessageHandler);
                m_routingModel.RemoveNavModeSetCallback(m_navRoutingModeSetCallback);
                m_routingModel.RemoveRemainingRouteDurationSetCallback(m_remainingRouteDurationSetCallback);
                m_routingModel.RemoveCurrentDirectionSetCallback(m_currentDirectionSetCallback);
                m_routingModel.RemoveRouteClearedCallback(m_routeClearedCallback);
                m_routingModel.RemoveRouteSetCallback(m_routeSetCallback);
                m_routingModel.RemoveEndLocationClearedCallback(m_endLocationClearedCallback);
                m_routingModel.RemoveEndLocationSetCallback(m_endLocationSetCallback);
                m_routingModel.RemoveStartLocationClearedCallback(m_startLocationClearedCallback);
                m_routingModel.RemoveStartLocationSetCallback(m_startLocationSetCallback);
            }

            void NavRoutingController::OnStartLocationSet(const SdkModel::NavRoutingLocationModel& startLocation)
            {
                m_messageBus.Publish(NavRoutingStartLocationSetMessage(startLocation));
            }

            void NavRoutingController::OnStartLocationCleared()
            {
                m_messageBus.Publish(NavRoutingStartLocationClearedMessage());
            }

            void NavRoutingController::OnEndLocationSet(const SdkModel::NavRoutingLocationModel& endLocation)
            {
                m_messageBus.Publish(NavRoutingEndLocationSetMessage(endLocation));
            }

            void NavRoutingController::OnEndLocationCleared()
            {
                m_messageBus.Publish(NavRoutingEndLocationClearedMessage());
            }

            void NavRoutingController::OnRouteSet(const SdkModel::NavRoutingRouteModel& routeModel)
            {
                m_messageBus.Publish(NavRoutingRouteSetMessage(routeModel));
                m_routingModel.SetNavMode(Ready);
                m_routingModel.SetRemainingRouteDuration(routeModel.GetDuration());
            }

            void NavRoutingController::OnRouteCleared()
            {
                m_messageBus.Publish(NavRoutingRouteClearedMessage());
                m_routingModel.SetNavMode(NotReady);
                m_routingModel.SetRemainingRouteDuration(0);
            }

            void NavRoutingController::OnCurrentDirectionSet(const int& directionIndex)
            {
                m_messageBus.Publish(NavRoutingCurrentDirectionSetMessage(directionIndex));
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
                        m_routingModel.SetNavMode(NavRoutingMode::Ready);
                        break;
                    case NavRoutingMode::Ready:
                        m_routingModel.SetNavMode(NavRoutingMode::Active);
                        break;
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
                if(m_locationService.GetIsAuthorized())
                {
                    Eegeo::Space::LatLong currentLocation = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                    if(m_locationService.GetLocation(currentLocation))
                    {
                        int indoorMapFloorId = 0;
                        m_locationService.GetFloorIndex(indoorMapFloorId);

                        m_routingModel.SetStartLocation(SdkModel::NavRoutingLocationModel("Current Location",
                                                                                       currentLocation,
                                                                                       m_locationService.IsIndoors(),
                                                                                       m_locationService.GetInteriorId(),
                                                                                       indoorMapFloorId));
                    }
                }

                const Search::SdkModel::SearchResultModel& searchResultModel = message.GetModel();
                m_routingModel.SetEndLocation(SdkModel::NavRoutingLocationModel(searchResultModel.GetTitle(),
                                                                                searchResultModel.GetLocation(),
                                                                                searchResultModel.IsInterior(),
                                                                                searchResultModel.GetBuildingId(),
                                                                                searchResultModel.GetFloor()));

                m_messageBus.Publish(NavRoutingViewOpenMessage(m_routingModel));
            }
        }
    }
}
