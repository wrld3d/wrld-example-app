// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultPoiView.h"
#include "CallbackCollection.h"
#include "SearchResultPoiView.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewInterop : public ISearchResultPoiView
            {
            private:
                SearchResultPoiView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_closeClickedCallbacks;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_togglePinClickedCallbacks;

            public:
                SearchResultPoiViewInterop(SearchResultPoiView* pView);

                void Show(const Search::SdkModel::SearchResultModel model,
                          bool isPinned);

                void Hide();

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleCloseClicked();
                
                void InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void HandlePinToggleClicked(Search::SdkModel::SearchResultModel& searchResultModel);
            };
        }
    }
}
