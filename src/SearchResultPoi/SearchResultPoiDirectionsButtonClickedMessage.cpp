// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiDirectionsButtonClickedMessage.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiDirectionsButtonClickedMessage::SearchResultPoiDirectionsButtonClickedMessage(const Search::SdkModel::SearchResultModel& model)
                : m_model(model)
        {

        }

        const Search::SdkModel::SearchResultModel& SearchResultPoiDirectionsButtonClickedMessage::GetModel() const
        {
            return m_model;
        }
    }
}
