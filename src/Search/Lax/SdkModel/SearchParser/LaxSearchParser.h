// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>

#include "Types.h"

#include "Search.h"

#include "LaxMeetingRoomResultModel.h"
#include "LaxTransitionResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                namespace SearchParser
                {
                    ExampleApp::Search::SdkModel::SearchResultModel MutateMeetingRoomAvailability(const Search::SdkModel::SearchResultModel& searchResultModel, const std::string& newAvailability);
                    
                    LaxMeetingRoomResultModel TransformToLaxMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    LaxTransitionResultModel TransformToLaxTransitionResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
                    
                    std::string GetFormattedAvailabilityString(const std::string& availabilityString);
                }
            }
        }
    }
}