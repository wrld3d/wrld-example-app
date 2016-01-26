// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        class SearchResultRemovedMessage
        {
            Search::SdkModel::SearchResultModel m_model;

        public:
            SearchResultRemovedMessage(const Search::SdkModel::SearchResultModel& model);

            const Search::SdkModel::SearchResultModel& Model() const;
        };
    }
}
