// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "ISearchProvider.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
        class DummySearchProvider : public SearchMenu::View::ISearchProvider, private Eegeo::NonCopyable
        {
        private:
            
        public:
            DummySearchProvider();
            ~DummySearchProvider();
            
            typedef std::vector<SearchMenu::View::SearchServicesResult> TSearchResults;
            
            void InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
            void RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
            
            void InsertSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback);
            void RemoveSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback);
            
            void InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
            void RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback);
            
            void OnSearchResponseReceived(const TSearchResults& searchResults);
        };
    }
}
