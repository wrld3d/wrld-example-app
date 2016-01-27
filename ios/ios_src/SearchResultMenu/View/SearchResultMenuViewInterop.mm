// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuViewInterop::SearchResultMenuViewInterop(SearchResultMenuView* pView)
            : m_pView(pView)
            {
            }
            
            void SearchResultMenuViewInterop::SetHeader(const std::string& header, bool queryPending, size_t numResult)
            {
                [m_pView updateViewForQuery :header :queryPending :numResult];
                
            }
            
            void SearchResultMenuViewInterop::SetAttractMode(bool attractModeEnabled)
            {
                [m_pView setAttractMode :attractModeEnabled];
            }
            
            void SearchResultMenuViewInterop::InsertSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }
            
            void SearchResultMenuViewInterop::RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void SearchResultMenuViewInterop::SearchClosed()
            {
                m_callbacks.ExecuteCallbacks();
            }
        }
    }
}