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

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<ISearchResultPoiView> m_view;
                const std::shared_ptr<ISearchResultPoiViewModel> m_viewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, Search::SdkModel::SearchResultModel> m_togglePinnedCallback;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, const SearchResultPoiViewImageDownloadCompletedMessage&> m_imageLoadedHandlerBinding;

                void OnViewClosed();

                void OnCloseButtonClicked();
                
                void OnPinToggledButtonClicked(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void OnSearchResultImageLoaded(const SearchResultPoiViewImageDownloadCompletedMessage& message);

            protected:
                ISearchResultPoiView& GetView() { return *m_view; }
                ISearchResultPoiViewModel& GetViewModel() { return *m_viewModel; }
                ExampleAppMessaging::TMessageBus& GetMessageBus() { return *m_messageBus; }

                virtual void OnViewOpened();
            public:
                SearchResultPoiController(const std::shared_ptr<ISearchResultPoiView>& view,
                                          const std::shared_ptr<ISearchResultPoiViewModel>& viewModel,
                                          const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                          const std::shared_ptr<Metrics::IMetricsService>& metricsService);

                virtual ~SearchResultPoiController();
            };
        }
    }
}
