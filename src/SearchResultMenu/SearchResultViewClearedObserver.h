//  Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

#include "Types.h"
#include "ISearchQueryPerformer.h"
#include "UiToNativeMessageBus.h"
#include "SearchResultViewClearedMessage.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultViewClearedObserver : private Eegeo::NonCopyable
        {
        private:
            Search::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            Eegeo::Helpers::TCallback1<SearchResultViewClearedObserver, const SearchResultViewClearedMessage&> m_handler;
        
            void OnSearchResultViewCleared(const SearchResultViewClearedMessage& message)
            {
                m_searchQueryPerformer.RemoveSearchQueryResults();
            }
            
        public:
            SearchResultViewClearedObserver(Search::ISearchQueryPerformer& searchQueryPerformer,
                                            ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
            : m_searchQueryPerformer(searchQueryPerformer)
            , m_uiToNativeMessageBus(uiToNativeMessageBus)
            , m_handler(this, &SearchResultViewClearedObserver::OnSearchResultViewCleared)
            {
                m_uiToNativeMessageBus.Subscribe(m_handler);
            }
            
            ~SearchResultViewClearedObserver()
            {
                m_uiToNativeMessageBus.Unsubscribe(m_handler);
            }
        };
    }
}