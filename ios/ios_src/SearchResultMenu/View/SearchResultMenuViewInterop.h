// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultMenuView.h"
#include "SearchResultMenuView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuViewInterop : private Eegeo::NonCopyable, public ISearchResultMenuView
            {
            private:
                SearchResultMenuView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                SearchResultMenuViewInterop(SearchResultMenuView* pView)
                    : m_pView(pView)
                {
                }

                void SetHeader(const std::string& header, bool queryPending, size_t numResult)
                {
                    [m_pView updateViewForQuery :header :queryPending :numResult];
                }
                
                void SetAttractMode(bool attractModeEnabled)
                {
                    [m_pView setAttractMode :attractModeEnabled];
                }
                
                void InsertSearchClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_callbacks.AddCallback(callback);
                }

                void RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback)
                {
                    m_callbacks.RemoveCallback(callback);
                }

                void SearchClosed()
                {
                    m_callbacks.ExecuteCallbacks();
                }
            };
        }
    }
}
