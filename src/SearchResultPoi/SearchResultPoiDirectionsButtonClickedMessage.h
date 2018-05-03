// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        class SearchResultPoiDirectionsButtonClickedMessage
        {
        private:
            Search::SdkModel::SearchResultModel m_model;

        public:
            SearchResultPoiDirectionsButtonClickedMessage(const Search::SdkModel::SearchResultModel& model);

            const Search::SdkModel::SearchResultModel& GetModel() const;
        };
    }
}
