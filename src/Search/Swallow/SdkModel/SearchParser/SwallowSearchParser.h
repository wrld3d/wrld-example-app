// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>

#include "Types.h"

#include "Search.h"
#include "SwallowPersonResultModel.h"
#include "SwallowMeetingRoomResultModel.h"
#include "SwallowWorkingGroupResultModel.h"
#include "SwallowFacilityResultModel.h"
#include "SwallowDepartmentResultModel.h"
#include "SwallowOfficeResultModel.h"
#include "SwallowTransitionResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                namespace SearchParser
                {
                    ExampleApp::Search::SdkModel::SearchResultModel MutateMeetingRoomAvailability(const Search::SdkModel::SearchResultModel& searchResultModel, const std::string& newAvailability);
                    
                    SwallowPersonResultModel TransformToSwallowPersonResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowMeetingRoomResultModel TransformToSwallowMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowWorkingGroupResultModel TransformToSwallowWorkingGroupResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowFacilityResultModel TransformToSwallowFacilityResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowDepartmentResultModel TransformToSwallowDepartmentResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowOfficeResultModel TransformToSwallowOfficeResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowTransitionResultModel TransformToSwallowTransitionResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
                    
                    std::string GetFormattedAvailabilityString(const std::string& availabilityString);
                }
            }
        }
    }
}