// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"
#include <string>

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultMeetingAvailabilityChanged
        {
        public:
            SearchResultMeetingAvailabilityChanged(const Search::SdkModel::SearchResultModel& model, const std::string& availability);
            
            const Search::SdkModel::SearchResultModel& GetModel() const;
            
            const std::string& GetAvailability() const;
            
        private:
            const Search::SdkModel::SearchResultModel m_model;
            const std::string m_availability;
        };
    }
}
