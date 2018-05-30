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
#include "InteriorsModelRepository.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingController : private Eegeo::NonCopyable
            {
            public:
                NavRoutingController(INavRoutingModel& routingModel,
                                     Eegeo::Location::ILocationService& locationService,
                                     TurnByTurn::INavTurnByTurnModel& turnByTurnModel,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                     Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);

                ~NavRoutingController();

            private:
                INavRoutingModel& m_routingModel;
                Eegeo::Location::ILocationService& m_locationService;
                TurnByTurn::INavTurnByTurnModel& m_turnByTurnModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;

                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingRouteModel&> m_routeSetCallback;
                Eegeo::Helpers::TCallback0<NavRoutingController> m_routeClearedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const int> m_currentDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingDirectionModel&> m_currentDirectionUpdatedCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const int> m_selectedDirectionSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const double> m_remainingRouteDurationSetCallback;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingMode> m_navRoutingModeSetCallback;

                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingViewClosedMessage&> m_viewClosedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingViewStartEndLocationSwappedMessage&> m_startEndLocationSwappedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingStartLocationClearClickedMessage&> m_startLocationClearClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingEndLocationClearClickedMessage&> m_endLocationClearClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingStartEndRoutingButtonClickedMessage&> m_startEndRoutingButtonClickedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const NavRoutingSelectedDirectionChangedMessage&> m_selectedDirectionChangedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingController, const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage&> m_directionsButtonClickedMessageHandler;
                
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<NavRoutingController> m_failAlertHandler;


                void OnStartLocationSet(const NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void OnRouteSet(const NavRoutingRouteModel& routeModel);

                void OnRouteCleared();

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

                void OnDirectionsButtonClicked(const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage& message);
                
                void OnFailAlertBoxDismissed();
            };
        }
    }
}
