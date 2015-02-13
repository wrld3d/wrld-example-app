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

            void SearchResultPoiViewInterop::Show(const Search::SdkModel::SearchResultModel model,
                                                  bool isPinned)
            {
                [m_pView setFullyActive];
                [m_pView setContent:&model :isPinned];
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
            
            void SearchResultPoiViewInterop::InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_togglePinClickedCallbacks.AddCallback(callback);
            }
            
            void SearchResultPoiViewInterop::RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                m_togglePinClickedCallbacks.RemoveCallback(callback);
            }
            
            void SearchResultPoiViewInterop::HandlePinToggleClicked(Search::SdkModel::SearchResultModel& searchResultModel)
            {
                m_togglePinClickedCallbacks.ExecuteCallbacks(searchResultModel);
            }
        }
    }
}