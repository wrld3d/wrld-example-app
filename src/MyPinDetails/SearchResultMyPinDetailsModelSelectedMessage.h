// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class SearchResultMyPinDetailsModelSelectedMessage
        {
        private:
            Search::SdkModel::SearchResultModel m_searchResultModel;
            
        public:
            SearchResultMyPinDetailsModelSelectedMessage(const Search::SdkModel::SearchResultModel& searchResultModel);
            
            const Search::SdkModel::SearchResultModel& GetSearchResultModel() const;
        };
    }
}
