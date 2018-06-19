#pragma once

#include "Types.h"
#include "ISearchProvider.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchResultsRepository
            {
            public:

                typedef Search::SdkModel::SearchResultModel TSdkSearchResult;

                virtual ~ISearchResultsRepository() {}

                virtual ISearchProvider::TSearchResults& GetResults() = 0;
                virtual void SetResults(const std::vector<TSdkSearchResult>& sdkResults) = 0;
                virtual const int GetResultOriginalIndexFromCurrentIndex(int index) const = 0;
                virtual const SearchServicesResult::TSdkSearchResult& GetSdkSearchResultByIndex(int index) const = 0;
            };
        }
    }
}
