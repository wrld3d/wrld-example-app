// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavigateToMessage
        {
        private:
            const SearchNavigationData m_data;
            const Search::SdkModel::SearchResultModel m_searchResultModel;

        public:
            NavigateToMessage(const SearchNavigationData data, const Search::SdkModel::SearchResultModel& searchResultModel);

            const SearchNavigationData& GetSearchData() const;
            const Search::SdkModel::SearchResultModel& GetSearchResultModel() const;
        };
    }
}
