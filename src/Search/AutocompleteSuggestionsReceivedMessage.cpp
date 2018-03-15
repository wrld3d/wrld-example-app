//
// Created by david.crooks on 13/03/2018.
//

#include "AutocompleteSuggestionsReceivedMessage.h"
namespace ExampleApp
{
    namespace Search
    {
        AutocompleteSuggestionsReceivedMessage::AutocompleteSuggestionsReceivedMessage(const SdkModel::SearchQuery& query,
                                                                               const std::vector<SdkModel::SearchResultModel>& results)
                : m_query(query)
                , m_results(results)
        {

        }

        const SdkModel::SearchQuery AutocompleteSuggestionsReceivedMessage::GetQuery() const
        {
            return m_query;
        }

        const std::vector<SdkModel::SearchResultModel>& AutocompleteSuggestionsReceivedMessage::GetResults() const
        {
            return m_results;
        }
    }
}