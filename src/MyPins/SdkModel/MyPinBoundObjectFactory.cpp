// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinBoundObjectFactory.h"
#include "MyPinModel.h"
#include "UserCreatedPinBoundObject.h"
#include "SearchResultPinBoundObject.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinBoundObjectFactory::MyPinBoundObjectFactory(ExampleAppMessaging::TMessageBus& messageBus,
                                                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                             Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                             MyPinsWebService& webService)
            : m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_myPinsSearchResultRefreshService(myPinsSearchResultRefreshService)
            , m_webService(webService)
            {
                
            }
            
            MyPinBoundObjectFactory::~MyPinBoundObjectFactory()
            {
                
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreateUserCreatedPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                                        MyPinModel::TPinIdType pinId,
                                                                                        Byte* imageData,
                                                                                        size_t imageSize,
                                                                                        bool share,
                                                                                        const std::string& pinIconKey)
            {
                return Eegeo_NEW(UserCreatedPinBoundObject)(pinId,
                                                            imageData,
                                                            imageSize,
                                                            share,
                                                            pinIconKey,
                                                            myPinsFileIO,
                                                            m_messageBus,
                                                            m_webService);
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreateSearchResultPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                                         MyPinModel::TPinIdType pinId,
                                                                                         const Search::SdkModel::SearchResultModel& searchResult,
                                                                                         const std::string& pinIconKey,
                                                                                         ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            {
                return Eegeo_NEW(SearchResultPinBoundObject)(pinId,
                                                             searchResult,
                                                             pinIconKey,
                                                             myPinsFileIO,
                                                             m_myPinsSearchResultRefreshService,
                                                             m_messageBus,
                                                             m_sdkModelDomainEventBus,
                                                             myPinsService);
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreatePinBoundObjectFromSerialized(MyPinsFileIO& myPinsFileIO,
                                                                                           MyPinModel::TPinIdType pinId,
                                                                                           const MyPinsSemanticPinType& semanticPinType,
                                                                                           const std::string& pinMetadataJson,
                                                                                           const std::string& pinIconKey,
                                                                                           ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            {
                switch (semanticPinType)
                {
                    case UserCreatedPoi:
                    {
                        return UserCreatedPinBoundObject::FromSerializedData(pinId,
                                                                             pinMetadataJson,
                           													 pinIconKey,
                                                                             myPinsFileIO,
                                                                             m_messageBus,
                                                                             m_webService);
                    }break;
                        
                    case SearchResultPoi:
                    {
                        return SearchResultPinBoundObject::FromSerializedData(pinId,
                                                                              pinMetadataJson,
                                                                              pinIconKey,
                                                                              myPinsFileIO,
                                                                              m_myPinsSearchResultRefreshService,
                                                                              m_messageBus,
                                                                              m_sdkModelDomainEventBus,
                                                                              myPinsService
                                                                              );
                    }break;
                        
                    default:
                    {
                        Eegeo_ASSERT(false, "Unrecognised MyPins type.\n")
                    }break;
                }
                
                return NULL;
            }
        }
    }
}
