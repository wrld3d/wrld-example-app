// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModelSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapItemModelSelectedMessage::SearchResultOnMapItemModelSelectedMessage(const Search::SdkModel::SearchResultModel& model)
            : m_model(model)
        {
        }

        const Search::SdkModel::SearchResultModel& SearchResultOnMapItemModelSelectedMessage::GetModel() const
        {
            return m_model;
        }
    }
}
