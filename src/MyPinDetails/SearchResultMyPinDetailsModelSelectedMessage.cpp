// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMyPinDetailsModelSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        SearchResultMyPinDetailsModelSelectedMessage::SearchResultMyPinDetailsModelSelectedMessage(const Search::SdkModel::SearchResultModel& searchResultModel)
        : m_searchResultModel(searchResultModel)
        {
            
        }
        
        const Search::SdkModel::SearchResultModel& SearchResultMyPinDetailsModelSelectedMessage::GetSearchResultModel() const
        {
            return m_searchResultModel;
        }
    }
}
