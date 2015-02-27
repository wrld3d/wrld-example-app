// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "IMyPinsSearchResultRefreshService.h"
#include "ISearchResultMyPinsService.h"
#include "Types.h"
#include "MyPins.h"
#include "ICallback.h"
#include "MyPinModel.h"
#include "IdentitySearchCallbackData.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {
                class MyPinsSearchResultRefreshService : public IMyPinsSearchResultRefreshService, private Eegeo::NonCopyable
                {
                    typedef std::map<std::string, ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType> TIdentifierToPinIdMap;
                    typedef std::map<ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType, ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject*>  TPinIdToBoundObjectMap;
                    
                    TIdentifierToPinIdMap m_vendorIdToPinMap;
                    TPinIdToBoundObjectMap m_pinIdToSearchResultPinBoundObject;
                    
                    ISearchResultMyPinsService& m_searchResultMyPinsService;
                    Search::SdkModel::ISearchService& m_searchService;
                    
                    Eegeo::Helpers::TCallback1<MyPinsSearchResultRefreshService, const SdkModel::IdentitySearchCallbackData&> m_refreshSearchResultCompletedHandler;
                    
                    void HandleRefreshSearchResultCompleted(const SdkModel::IdentitySearchCallbackData& result);
                    
                public:
                    MyPinsSearchResultRefreshService(ISearchResultMyPinsService& searchResultMyPinsService,
                                                     Search::SdkModel::ISearchService& searchService);
                    
                    ~MyPinsSearchResultRefreshService();
                    
                    void RefreshPinnedSearchResult(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                   ExampleApp::MyPins::SdkModel::SearchResultPinBoundObject& searchResultPinBoundObject,
                                                   const SearchResultModel& searchResultModel);
                };
            }
        }
    }
}
