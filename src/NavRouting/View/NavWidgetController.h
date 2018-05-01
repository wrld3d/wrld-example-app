// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"
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
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback1<NavWidgetController, const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage&> m_directionsButtonClickedMessageHandler;

                void OnViewClosed();

                void OnCloseButtonClicked();

                void OnDirectionsButtonClicked(const SearchResultPoi::SearchResultPoiDirectionsButtonClickedMessage& message);

            protected:
                INavWidgetView& GetView() { return m_view; }
                INavWidgetViewModel& GetViewModel() { return m_viewModel; }
                ExampleAppMessaging::TMessageBus& GetMessageBus() { return m_messageBus; }

                virtual void OnViewOpened();
            public:
                NavWidgetController(INavWidgetView& view,
                                    INavWidgetViewModel& viewModel,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                virtual ~NavWidgetController();
            };
        }
    }
}
