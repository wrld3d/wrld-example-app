// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultAddedMessage.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        SearchResultAddedMessage::SearchResultAddedMessage(const Search::SdkModel::SearchResultModel& model)
        : m_model(model)
        {
            
        }

        const Search::SdkModel::SearchResultModel& SearchResultAddedMessage::Model() const
        {
            return m_model;
        }
    }
}
