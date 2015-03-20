// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "MyPinModel.h"
#include "SearchResultPinBoundObject.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {
                class IMyPinsSearchResultRefreshService
                {
                public:
                    virtual ~IMyPinsSearchResultRefreshService() { }
                    
                    virtual void RefreshPinnedSearchResult(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                           ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject& searchResultPinBoundObject,
                                                           const SearchResultModel& searchResultModel) = 0;
                };
            }
        }
    }
}
