//
// Created by david.crooks on 13/03/2018.
//

#pragma once

#include <vector>
#include "SearchQuery.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        class AutocompleteSuggestionsReceivedMessage
        {
        private:
            const bool m_didSucceed;
            const SdkModel::SearchQuery m_query;
            const std::vector<SdkModel::SearchResultModel> m_results;

        public:
            AutocompleteSuggestionsReceivedMessage(const bool didSucceed,
                                                   const SdkModel::SearchQuery& query,
                                                   const std::vector<SdkModel::SearchResultModel>& results);
            
            const bool DidSucceed() const;
            
            const SdkModel::SearchQuery GetQuery() const;

            const std::vector<SdkModel::SearchResultModel>& GetResults() const;
        };
    }
}

