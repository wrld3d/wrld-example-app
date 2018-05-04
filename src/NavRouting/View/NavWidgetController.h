// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "ILocationService.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"
#include "NavRoutingLocationModel.h"
#include "SearchResultPoiDirectionsButtonClickedMessage.h"

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
                Eegeo::Location::ILocationService& m_locationService;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback0<NavWidgetController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startLocationClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_endLocationClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startLocationClearButtonClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_endLocationClearButtonClickedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startEndLocationsSwappedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const SdkModel::NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const SdkModel::NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage&> m_directionsButtonClickedMessageHandler;

                void OnCloseButtonClicked();

                void OnStartLocationClicked();

                void OnEndLocationClicked();

                void OnStartLocationClearButtonClicked();

                void OnEndLocationClearButtonClicked();

                void OnStartEndLocationsSwapped();

                void OnViewClosed();

                void OnStartLocationSet(const SdkModel::NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const SdkModel::NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void OnDirectionsButtonClicked(const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage& message);

            protected:
                INavWidgetView& GetView() { return m_view; }
                INavWidgetViewModel& GetViewModel() { return m_viewModel; }
                ExampleAppMessaging::TMessageBus& GetMessageBus() { return m_messageBus; }

                virtual void OnViewOpened();
            public:
                NavWidgetController(INavWidgetView& view,
                                    INavWidgetViewModel& viewModel,
                                    Eegeo::Location::ILocationService& locationService,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                virtual ~NavWidgetController();
            };
        }
    }
}
