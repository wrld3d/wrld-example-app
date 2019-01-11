// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "NavRouting.h"
#include "INavRoutingModel.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"
#include "INavRoutingServiceController.h"
#include "NavRoutingViewClosedMessage.h"
#include "NavRoutingViewStartEndLocationSwappedMessage.h"
#include "NavRoutingStartLocationClearClickedMessage.h"
#include "NavRoutingEndLocationClearClickedMessage.h"
#include "NavRoutingSelectedDirectionChangedMessage.h"
#include "NavRoutingStartEndRoutingButtonClickedMessage.h"
#include "NavRoutingRerouteDialogClosedMessage.h"
#include "InteriorsModelRepository.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "WorldPins.h"
#include "INavRoutingLocationFinder.h"
#include "NavRoutingStartLocationSetFromSearchMessage.h"
#include "NavRoutingEndLocationSetFromSearchMessage.h"
#include "NavRoutingSearchForLocationMessage.h"
#include "AppCamera.h"
#include "Search.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingController
            {
            public:
                NavRoutingController(INavRoutingModel& routingModel,
                                     TurnByTurn::INavTurnByTurnModel& turnByTurnModel,
                                     INavRoutingLocationFinder& locationFinder,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                     INavRoutingCustomLocationPicker& m_customLocationPicker,
                                     Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                     INavRoutingHighlightsController& highlightsController,
                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);

                ~NavRoutingController();

                void OpenViewWithModel(INavRoutingModel& routingModel);
                void Update();

            private:
                INavRoutingModel& m_routingModel;
                TurnByTurn::INavTurnByTurnModel& m_turnByTurnModel;
                INavRoutingLocationFinder& m_locationFinder;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                INavRoutingCustomLocationPicker& m_customLocationPicker;
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                INavRoutingHighlightsController& m_highlightsController;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;

                bool m_isRerouting;
                bool m_waitingForRerouteResponse;
                bool m_hasUpdatedSelectedDirection;
                bool m_isSearching;

                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_routeClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingRouteModel&> m_routeUpdatedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const int> m_currentDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingDirectionModel&> m_currentDirectionUpdatedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const int> m_selectedDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const double> m_remainingRouteDurationSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingMode> m_navRoutingModeSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_interiorLocationLostCallback;

                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingViewClosedMessage&> m_viewClosedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingViewStartEndLocationSwappedMessage&> m_startEndLocationSwappedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingStartLocationClearClickedMessage&> m_startLocationClearClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingEndLocationClearClickedMessage&> m_endLocationClearClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingStartEndRoutingButtonClickedMessage&> m_startEndRoutingButtonClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingSelectedDirectionChangedMessage&> m_selectedDirectionChangedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingRerouteDialogClosedMessage&> m_rerouteDialogClosedMessageMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRouting::NavigateToMessage&> m_navigateToMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingStartLocationSetFromSearchMessage&> m_startLocationSetFromSearchMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingEndLocationSetFromSearchMessage&> m_endLocationSetFromSearchMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingSearchForLocationMessage&> m_searchForLocationMessageHandler;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_interiorInteractionModelChangedHandler;

                Eegeo::Helpers::TCallback0<NavRoutingController> m_shouldRerouteCallback;

                void OnStartLocationSet(const NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void OnRouteSet(const NavRoutingRouteModel& routeModel);

                void OnRouteCleared();

                void OnRouteUpdated(const NavRoutingRouteModel& routeModel);

                void OnCurrentDirectionSet(const int& directionIndex);

                void OnCurrentDirectionUpdated(const NavRoutingDirectionModel& directionModel);

                void OnSelectedDirectionSet(const int& directionIndex);

                void OnRemainingRouteDurationSet(const double& seconds);

                void OnNavRoutingModeSet(const NavRoutingMode& mode);

                void OnNavWidgetViewClosed(const NavRoutingViewClosedMessage& message);

                void OnStartEndLocationSwapped(const NavRoutingViewStartEndLocationSwappedMessage& message);

                void OnStartLocationClearClicked(const NavRoutingStartLocationClearClickedMessage& message);

                void OnEndLocationClearClicked(const NavRoutingEndLocationClearClickedMessage& message);

                void OnStartEndRoutingButtonClicked(const NavRoutingStartEndRoutingButtonClickedMessage& message);

                void OnSelectedDirectionChanged(const NavRoutingSelectedDirectionChangedMessage& message);

                void OnRerouteDialogClosed(const NavRoutingRerouteDialogClosedMessage& message);

                void OnNavigationMessage(const NavigateToMessage& message);

                void OnShouldReroute();

                void OnStartLocationSetFromSearch(const NavRoutingStartLocationSetFromSearchMessage& message);

                void OnEndLocationSetFromSearch(const NavRoutingEndLocationSetFromSearchMessage& message);

                void OnSearchForLocation(const NavRoutingSearchForLocationMessage& message);

                void OnInteritorLocationLost();

                void OnInteriorChanged();
            };
        }
    }
}
