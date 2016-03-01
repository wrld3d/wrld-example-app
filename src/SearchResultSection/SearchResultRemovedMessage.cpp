// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultRemovedMessage.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        SearchResultRemovedMessage::SearchResultRemovedMessage(
            const Search::SdkModel::SearchResultModel& model
        )
            : m_model(model)
        {
            
        }

        const Search::SdkModel::SearchResultModel& SearchResultRemovedMessage::Model() const
        {
            return m_model;
        }
    }
}
