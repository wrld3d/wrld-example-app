// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiPinToggledMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiPinToggledMessage::SearchResultPoiPinToggledMessage(const Search::SdkModel::SearchResultModel& model)
        : m_model(model)
        {
            
        }
        
        const Search::SdkModel::SearchResultModel& SearchResultPoiPinToggledMessage::GetModel() const
        {
            return m_model;
        }
    }
}
