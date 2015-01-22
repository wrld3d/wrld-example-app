// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultPoiView.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiView : public ISearchResultPoiView, Eegeo::NonCopyable
            {
            private:
                AndroidNativeState& m_nativeState;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;

                jclass m_uiViewClass;
                jobject m_uiView;
            public:
                SearchResultPoiView(AndroidNativeState& nativeState);

                ~SearchResultPoiView();

                void Show(const Search::SdkModel::SearchResultModel model);

                void Hide();

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleCloseClicked();
            };
        }
    }
}
