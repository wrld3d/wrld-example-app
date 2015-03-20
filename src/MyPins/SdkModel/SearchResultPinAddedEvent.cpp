// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPinAddedEvent.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            SearchResultPinAddedEvent::SearchResultPinAddedEvent(const SdkModel::MyPinModel& pinModel,
                                                                 const Search::SdkModel::SearchResultModel& searchResultModel)
            : m_pinModel(pinModel)
            , m_searchResultModel(searchResultModel)
            {
                
            }
            
            const SdkModel::MyPinModel& SearchResultPinAddedEvent::GetMyPinModel() const
            {
                return m_pinModel;
            }
            
            const Search::SdkModel::SearchResultModel& SearchResultPinAddedEvent::GetSearchResultModel() const
            {
                return m_searchResultModel;
            }
        }
    }
}
