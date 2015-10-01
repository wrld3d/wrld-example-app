// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>

#include "Types.h"

#include "Search.h"
#include "SwallowPersonResultModel.h"
#include "SwallowMeetingRoomResultModel.h"
#include "SwallowWorkingGroupResultModel.h"
#include "SwallowFacilityResultModel.h"
#include "SwallowOfficeResultModel.h"

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
                    SwallowPersonResultModel TransformToSwallowPersonResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowMeetingRoomResultModel TransformToSwallowMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowWorkingGroupResultModel TransformToSwallowWorkingGroupResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowFacilityResultModel TransformToSwallowFacilityResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    SwallowOfficeResultModel TransformToSwallowOfficeResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                }
            }
        }
    }
}