// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class ISearchResultPoiMyPinService
            {
            public:
                virtual ~ISearchResultPoiMyPinService() { }
                
                virtual void AddOrRemoveSearchResultFromMyPins(const Search::SdkModel::SearchResultModel& searchResult) = 0;
            };
        }
    }
}
