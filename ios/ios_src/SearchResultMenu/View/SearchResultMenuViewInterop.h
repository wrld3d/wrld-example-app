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
                SearchResultMenuViewInterop(SearchResultMenuView* pView);

                void SetHeader(const std::string& header, bool queryPending, size_t numResult);
                void SetAttractMode(bool attractModeEnabled);
                
                void InsertSearchClosed(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback);

                void SearchClosed();
            };
        }
    }
}
