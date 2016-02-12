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
                                                             CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                                             Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService)
            : m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_categorySearchRepository(categorySearchRepository)
            , m_myPinsSearchResultRefreshService(myPinsSearchResultRefreshService)
            {
                
            }
            
            MyPinBoundObjectFactory::~MyPinBoundObjectFactory()
            {
                
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreateUserCreatedPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                                        MyPinModel::TPinIdType pinId,
                                                                                        Byte* imageData,
                                                                                        size_t imageSize,
                                                                                        bool share)
            {
                return Eegeo_NEW(UserCreatedPinBoundObject)(pinId,
                                                            imageData,
                                                            imageSize,
                                                            share,
                                                            myPinsFileIO,
                                                            m_messageBus);
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreateSearchResultPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                                         MyPinModel::TPinIdType pinId,
                                                                                         const Search::SdkModel::SearchResultModel& searchResult,
                                                                                         ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            {
                return Eegeo_NEW(SearchResultPinBoundObject)(pinId,
                                                             searchResult,
                                                             myPinsFileIO,
                                                             m_categorySearchRepository,
                                                             m_myPinsSearchResultRefreshService,
                                                             m_messageBus,
                                                             m_sdkModelDomainEventBus,
                                                             myPinsService);
            }
            
            IMyPinBoundObject* MyPinBoundObjectFactory::CreatePinBoundObjectFromSerialized(MyPinsFileIO& myPinsFileIO,
                                                                                           MyPinModel::TPinIdType pinId,
                                                                                           const MyPinsSemanticPinType& semanticPinType,
                                                                                           const std::string& serializedData,
                                                                                           ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            {
                switch (semanticPinType)
                {
                    case UserCreatedPoi:
                    {
                        return UserCreatedPinBoundObject::FromSerializedData(pinId,
                                                                             serializedData,
                                                                             myPinsFileIO,
                                                                             m_messageBus);
                    }break;
                        
                    case SearchResultPoi:
                    {
                        return SearchResultPinBoundObject::FromSerializedData(pinId,
                                                                              serializedData,
                                                                              myPinsFileIO,
                                                                              m_categorySearchRepository,
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
