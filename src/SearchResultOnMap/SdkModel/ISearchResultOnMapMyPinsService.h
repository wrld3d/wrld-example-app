// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class ISearchResultOnMapMyPinsService
            {
            public:
                virtual ~ISearchResultOnMapMyPinsService() { }
                
                virtual bool IsSearchResultPinned(const Search::SdkModel::SearchResultModel& seachResult) const = 0;
                
                virtual void InsertSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                
                virtual void RemoveSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                
                virtual void InsertSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                
                virtual void RemoveSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
            };
        }
    }
}
