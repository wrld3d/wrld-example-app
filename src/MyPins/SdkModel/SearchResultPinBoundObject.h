// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"
#include "IMyPinBoundObject.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "TagSearch.h"
#include "Search.h"
#include "Web.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class SearchResultPinBoundObject : public IMyPinBoundObject, private Eegeo::NonCopyable
            {
                Search::SdkModel::SearchResultModel m_searchResult;
                std::string m_pinIconKey;
                MyPinsFileIO& m_myPinsFileIO;
                Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& m_myPinsSearchResultRefreshService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                ExampleApp::MyPins::SdkModel::IMyPinsService& m_myPinsService;
                bool m_pinVendorRequiresRefreshing;
                bool m_isCurrentlyRefreshingResult;
                
                void SubmitPinToWebService(const MyPinModel& pinModel);
                
            public:
                static SearchResultPinBoundObject* FromSerializedData(MyPinModel::TPinIdType pinId,
                                                                      const std::string& serializedData,
                                                                      const std::string& pinIconKey,
                                                                      MyPinsFileIO& myPinsFileIO,
                                                                      Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                                      ExampleAppMessaging::TMessageBus& messageBus,
                                                                      ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                                      ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService);
                
                SearchResultPinBoundObject(MyPinModel::TPinIdType pinId,
                                           const Search::SdkModel::SearchResultModel& searchResult,
                                           const std::string& pinIconKey,
                                           MyPinsFileIO& myPinsFileIO,
                                           Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                           ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService);
                
                ~SearchResultPinBoundObject();
                
                void HandlePinCreated(const MyPinModel& pinModel);
                
                void HandlePinAdded(const MyPinModel& pinModel);
                
                void HandlePinRemoved(const MyPinModel& pinModel);
                
                void HandlePinDestroyed(const MyPinModel& pinModel);
                
                void HandlePinSelected(const MyPinModel& pinModel);
                
                void HandlePinBecameFullyVisible(const MyPinModel& pinModel);
                
                void HandlePinBecameFullyInvisible(const MyPinModel& pinModel);
                
                MyPinsSemanticPinType GetSemanticPinType() const;
                
                std::string GetIconForPin() const;
                
                std::string GetSerialized() const;
                
                void FinishRefreshingSearchResult(bool success,
                                                  const ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                  const Search::SdkModel::SearchResultModel& result);
            };
        }
    }
}
