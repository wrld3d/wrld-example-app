// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultPoiView.h"
#include "ISearchResultPoiViewModel.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "SearchResultModel.h"
#include "SearchResultPoiViewImageDownloadCompletedMessage.h"
#include "IMetricsService.h"
#include "ClosePoiMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiController : private Eegeo::NonCopyable
            {
            private:
                ISearchResultPoiView& m_view;
                ISearchResultPoiViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;

                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, Search::SdkModel::SearchResultModel> m_togglePinnedCallback;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, const SearchResultPoiViewImageDownloadCompletedMessage&> m_imageLoadedHandlerBinding;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, const Automation::ClosePoiMessage&> m_closePoiMessageHandler;

                void OnViewClosed();

                void OnCloseButtonClicked();
                
                void OnPinToggledButtonClicked(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void OnSearchResultImageLoaded(const SearchResultPoiViewImageDownloadCompletedMessage& message);
                
                void OnClosePoiMessageRecieved(const Automation::ClosePoiMessage& message);

            protected:
                ISearchResultPoiView& GetView() { return m_view; }
                ISearchResultPoiViewModel& GetViewModel() { return m_viewModel; }
                ExampleAppMessaging::TMessageBus& GetMessageBus() { return m_messageBus; }

                virtual void OnViewOpened();
            public:
                SearchResultPoiController(ISearchResultPoiView& view,
                                          ISearchResultPoiViewModel& viewModel,
                                          ExampleAppMessaging::TMessageBus& messageBus,
                                          Metrics::IMetricsService& metricsService);

                virtual ~SearchResultPoiController();
            };
        }
    }
}
