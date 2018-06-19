#pragma once

#include "Types.h"
#include "ISearchResultsRepository.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchResultsRepository : public ISearchResultsRepository
            {
            private:
                ISearchProvider::TSearchResults m_results;
            public:
                SearchResultsRepository();
                ISearchProvider::TSearchResults& GetResults();
                void SetResults(const std::vector<TSdkSearchResult>& sdkResults);
                const int GetResultOriginalIndexFromCurrentIndex(int index) const;
                const SearchServicesResult::TSdkSearchResult& GetSdkSearchResultByIndex(int index) const;
            };
        }
    }
}