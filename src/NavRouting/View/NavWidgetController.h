// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"
#include "NavRoutingViewOpenMessage.h"
#include "NavRoutingStartLocationSetMessage.h"
#include "NavRoutingStartLocationClearedMessage.h"
#include "NavRoutingEndLocationSetMessage.h"
#include "NavRoutingEndLocationClearedMessage.h"
#include "NavRoutingRouteChangedMessage.h"
#include "NavRoutingRouteClearedMessage.h"
#include "NavRoutingCurrentDirectionSetMessage.h"
#include "NavRoutingCurrentDirectionUpdatedMessage.h"
#include "NavRoutingRemainingRouteDurationSetMessage.h"
#include "NavRoutingModeSetMessage.h"
#include "NavRoutingShowRerouteDialogMessage.h"
#include "NavRoutingSetCalculatingRouteMessage.h"
#include "ISearchResultsRepository.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetController : private Eegeo::NonCopyable
            {
            private:
                INavWidgetView& m_view;
                INavWidgetViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback0<NavWidgetController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startLocationClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_endLocationClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startLocationClearButtonClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_endLocationClearButtonClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startEndLocationsSwappedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const int> m_selectedDirectionIndexChangedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const bool> m_rerouteDialogClosedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startEndRoutingButtonClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingStartLocationSetMessage&> m_startLocationSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingStartLocationClearedMessage&> m_startLocationClearedMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingEndLocationSetMessage&> m_endLocationSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingEndLocationClearedMessage&> m_endLocationClearedMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingRouteChangedMessage&> m_routeSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingRouteClearedMessage&> m_routeClearedMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingCurrentDirectionSetMessage&> m_currentDirectionSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingCurrentDirectionUpdatedMessage&> m_currentDirectionUpdatedMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingSelectedDirectionSetMessage&> m_selectedDirectionSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingRemainingRouteDurationSetMessage&> m_remainingRouteDurationSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingModeSetMessage&> m_navRoutingModeSetMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingViewOpenMessage&> m_navRoutingViewOpenMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingShowRerouteDialogMessage&> m_navRoutingShowRerouteDialogMessageMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetController, const NavRoutingSetCalculatingRouteMessage&> m_navRoutingSetCalculatingRouteMessageHandler;
                
                Eegeo::Helpers::TCallback1<NavWidgetController, const int> m_onNavigationStartPointFromResultCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const int> m_onNavigationEndPointFromResultCallback;
                Eegeo::Helpers::TCallback2<NavWidgetController, const bool, const bool> m_onSearchingForLocationCallback;

                void OnCloseButtonClicked();

                void OnStartLocationClicked();

                void OnEndLocationClicked();

                void OnStartLocationClearButtonClicked();

                void OnEndLocationClearButtonClicked();

                void OnStartEndLocationsSwapped();

                void OnSelectedDirectionIndexChanged(const int& selectedDirection);

                void OnRerouteDialogClosed(const bool& shouldReroute);

                void OnStartEndRoutingButtonClicked();

                void OnViewClosed();

                void OnStartLocationSet(const NavRoutingStartLocationSetMessage& message);

                void OnStartLocationCleared(const NavRoutingStartLocationClearedMessage& message);

                void OnEndLocationSet(const NavRoutingEndLocationSetMessage& message);

                void OnEndLocationCleared(const NavRoutingEndLocationClearedMessage& message);

                void OnRouteChanged(const NavRoutingRouteChangedMessage &message);

                void OnRouteCleared(const NavRoutingRouteClearedMessage& message);

                void OnCurrentDirectionSet(const NavRoutingCurrentDirectionSetMessage& message);

                void OnCurrentDirectionUpdated(const NavRoutingCurrentDirectionUpdatedMessage& message);

                void OnSelectedDirectionSet(const NavRoutingSelectedDirectionSetMessage& message);

                void OnRemainingRouteDurationSet(const NavRoutingRemainingRouteDurationSetMessage& message);

                void OnNavRoutingModeSet(const NavRoutingModeSetMessage& message);

                void OnNavRoutingViewOpen(const NavRoutingViewOpenMessage& message);

                void OnNavRoutingShowRerouteDialog(const NavRoutingShowRerouteDialogMessage& message);

                void OnNavigationStartPointFromResult(const int& index);

                void OnNavigationEndPointFromResult(const int& index);

                void OnSearchingForLocationChanged(const bool& isSearching, const bool& isStartLocation);
                
                void OnSetCalculateRouteSpinner(const NavRoutingSetCalculatingRouteMessage& message);
                
                SearchMenu::View::ISearchResultsRepository& m_searchResultsRepository;

            protected:
                INavWidgetView& GetView() { return m_view; }
                INavWidgetViewModel& GetViewModel() { return m_viewModel; }
                ExampleAppMessaging::TMessageBus& GetMessageBus() { return m_messageBus; }

                virtual void OnViewOpened();
            public:
                NavWidgetController(INavWidgetView& view,
                                    INavWidgetViewModel& viewModel,
                                    SearchMenu::View::ISearchResultsRepository& searchResultsRepository,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                virtual ~NavWidgetController();
            };
        }
    }
}
