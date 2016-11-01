// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Types.h"
#include "space.h"
#include <vector>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class DirectionMenuGeoNamesResponseReceivedMessage
        {
        private:
            
            const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& m_searchResults;
            
        public:
            DirectionMenuGeoNamesResponseReceivedMessage(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& results);
            
            const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>& SearchResults() const;
            
        };
    }
}