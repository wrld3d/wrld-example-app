// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMyPinBoundObjectFactory.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "TagSearch.h"
#include "Search.h"
#include "Web.h"

#include <memory>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinBoundObjectFactory : public IMyPinBoundObjectFactory, private Eegeo::NonCopyable
            {
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<ExampleAppMessaging::TSdkModelDomainEventBus> m_sdkModelDomainEventBus;
                const std::shared_ptr<Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService> m_myPinsSearchResultRefreshService;
                const std::shared_ptr<MyPinsWebService> m_webService;
                
            public:
                MyPinBoundObjectFactory(const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                        const std::shared_ptr<ExampleAppMessaging::TSdkModelDomainEventBus>& sdkModelDomainEventBus,
                                        const std::shared_ptr<Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService>& myPinsSearchResultRefreshService,
                                        const std::shared_ptr<MyPinsWebService>& webService);
                
                ~MyPinBoundObjectFactory();
                
                IMyPinBoundObject* CreateUserCreatedPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                   MyPinModel::TPinIdType pinId,
                                                                   Byte* imageData,
                                                                   size_t imageSize,
                                                                   bool share,
                                                                   const std::string& pinIconKey);
                
                IMyPinBoundObject* CreateSearchResultPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                    MyPinModel::TPinIdType pinId,
                                                                    const Search::SdkModel::SearchResultModel& searchResult,
                                                                    const std::string& pinIconKey,
                                                                    ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService);
                
                IMyPinBoundObject* CreatePinBoundObjectFromSerialized(MyPinsFileIO& myPinsFileIO,
                                                                      MyPinModel::TPinIdType pinId,
                                                                      const MyPinsSemanticPinType& semanticPinType,
                                                                      const std::string& pinMetadataJson,
                                                                      const std::string& pinIconKey,
                                                                      ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService);
            };
        }
    }
}
