// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "MyPins.h"
#include "ICallback.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {
                class ISearchResultMyPinsService
                {
                public:
                    virtual ~ISearchResultMyPinsService() { }
                    
                    virtual bool IsSearchResultPinned(const Search::SdkModel::SearchResultModel& seachResult) const = 0;
                    
                    virtual bool TryGetPinForSearchResult(const Search::SdkModel::SearchResultModel& searchResult,
                                                          ExampleApp::MyPins::SdkModel::MyPinModel& out_myPinModel) const = 0;

                    virtual bool TryGetPinTitleForSearchResultIdentifier(const std::string& identifier,
                                                                         std::string& out_pinTitle) const = 0;
                    
                    virtual bool ContainsPinWithId(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId) const = 0;
                    
                    virtual void InsertSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                    
                    virtual void RemoveSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                    
                    virtual void InsertSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                    
                    virtual void RemoveSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                };
            }
        }
    }
}
