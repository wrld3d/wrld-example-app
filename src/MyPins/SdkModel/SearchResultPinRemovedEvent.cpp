// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPinRemovedEvent.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            SearchResultPinRemovedEvent::SearchResultPinRemovedEvent(const SdkModel::MyPinModel& pinModel,
                                                                     const Search::SdkModel::SearchResultModel& searchResultModel)
            : m_pinModel(pinModel)
            , m_searchResultModel(searchResultModel)
            {
                
            }
            
            const SdkModel::MyPinModel& SearchResultPinRemovedEvent::GetMyPinModel() const
            {
                return m_pinModel;
            }
            
            const Search::SdkModel::SearchResultModel& SearchResultPinRemovedEvent::GetSearchResultModel() const
            {
                return m_searchResultModel;
            }
        }
    }
}
