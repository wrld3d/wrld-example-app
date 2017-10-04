// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "ISearchResultMyPinsService.h"
#include "Types.h"
#include "MyPins.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "SdkModelDomainEventBus.h"
#include "SearchResultPinAddedEvent.h"
#include "SearchResultPinRemovedEvent.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            namespace MyPins
            {
                class SearchResultMyPinsService : public ISearchResultMyPinsService, private Eegeo::NonCopyable
                {
                    ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                    Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_searchResultPinnedCallbacks;
                    Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_searchResultUnpinnedCallbacks;
                    
                    Eegeo::Helpers::TCallback1<SearchResultMyPinsService, const ExampleApp::MyPins::SdkModel::SearchResultPinAddedEvent&> m_searchResultPinAddedEventHandler;
                    Eegeo::Helpers::TCallback1<SearchResultMyPinsService, const ExampleApp::MyPins::SdkModel::SearchResultPinRemovedEvent&> m_searchResultPinRemovedEventHandler;
                    
                    typedef std::map<Search::SdkModel::SearchResultModel, ExampleApp::MyPins::SdkModel::MyPinModel> TSearchResultToPinIdMap;
                    
                    TSearchResultToPinIdMap m_searchResultToPinId;
                    
                    void OnSearchResultPinAddedEvent(const ExampleApp::MyPins::SdkModel::SearchResultPinAddedEvent& event);
                    
                    void OnSearchResultPinRemovedEvent(const ExampleApp::MyPins::SdkModel::SearchResultPinRemovedEvent& event);
                    
                public:
                    SearchResultMyPinsService(ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus);
                    
                    ~SearchResultMyPinsService();
                    
                    bool IsSearchResultPinned(const Search::SdkModel::SearchResultModel& searchResult) const;
                    
                    bool TryGetPinForSearchResult(const Search::SdkModel::SearchResultModel& searchResult,
                                                  ExampleApp::MyPins::SdkModel::MyPinModel& out_myPinModel) const;

                    bool TryGetPinTitleForSearchResultIdentifier(const std::string& identifier,
                                                                 std::string& out_pinTitle) const;
                    
                    bool ContainsPinWithId(ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId) const;
                    
                    void InsertSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                    
                    void RemoveSearchResultPinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                    
                    void InsertSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                    
                    void RemoveSearchResultUnpinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                };
            }
        }
    }
}
