// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultPoiView.h"
#include "ISearchResultPoiViewModel.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "SearchResultModel.h"

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

                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewOpenedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback0<SearchResultPoiController> m_closeButtonCallback;
                Eegeo::Helpers::TCallback1<SearchResultPoiController, Search::SdkModel::SearchResultModel> m_togglePinnedCallback;
                

                void OnViewOpened();

                void OnViewClosed();

                void OnCloseButtonClicked();
                
                void OnPinToggledButtonClicked(Search::SdkModel::SearchResultModel& searchResultModel);

            public:
                SearchResultPoiController(ISearchResultPoiView& view,
                                          ISearchResultPoiViewModel& viewModel,
                                          ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultPoiController();
            };
        }
    }
}
