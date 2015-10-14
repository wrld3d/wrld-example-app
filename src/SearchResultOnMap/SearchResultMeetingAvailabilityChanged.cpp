// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMeetingAvailabilityChanged.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultMeetingAvailabilityChanged::SearchResultMeetingAvailabilityChanged(const Search::SdkModel::SearchResultModel& model,
                                                                                             const std::string& availability)
        : m_model(model)
        , m_availability(availability)
        {
        }
        
        const Search::SdkModel::SearchResultModel& SearchResultMeetingAvailabilityChanged::GetModel() const
        {
            return m_model;
        }
        
        const std::string& SearchResultMeetingAvailabilityChanged::GetAvailability() const
        {
            return m_availability;
        }
    }
}
