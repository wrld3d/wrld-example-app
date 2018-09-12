// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavigateToMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavigateToMessage::NavigateToMessage(const SearchNavigationData data, const Search::SdkModel::SearchResultModel& searchResultModel)
        : m_data(data)
        , m_searchResultModel(searchResultModel)
        {

        }

        const SearchNavigationData& NavigateToMessage::GetSearchData() const
        {
            return m_data;
        }

        const Search::SdkModel::SearchResultModel& NavigateToMessage::GetSearchResultModel() const
        {
            return m_searchResultModel;
        }
    }
}
