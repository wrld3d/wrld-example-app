// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewInterop::SearchResultPoiViewInterop(SearchResultPoiView* pView) : m_pView(pView)
            {
            }

            void SearchResultPoiViewInterop::Show(const Search::SdkModel::SearchResultModel model)
            {
                [m_pView setFullyActive];
                [m_pView setContent:&model];
            }

            void SearchResultPoiViewInterop::Hide()
            {
                [m_pView setFullyInactive];
            }

            void SearchResultPoiViewInterop::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeClickedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiViewInterop::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeClickedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiViewInterop::HandleCloseClicked()
            {
                m_closeClickedCallbacks.ExecuteCallbacks();
            }
        }
    }
}