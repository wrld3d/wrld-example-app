// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsService.h"
#include "IMyPinsRepository.h"
#include "PinRepository.h"
#include "IWorldPinsFactory.h"
#include "Pin.h"
#include "MyPinsFileIO.h"
#include "ImageUploadData.h"
#include "IMenuOptionsModel.h"
#include "MyPinMenuOption.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"
#include "IMyPinSelectionHandlerFactory.h"
#include "IMyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPinSelectionHandler.h"
#include "MyPinsSemanticPinType.h"
#include "IMyPinBoundObjectFactory.h"
#include "IMyPinBoundObjectRepository.h"
#include "IMyPinBoundObject.h"
#include <string>
#include <sstream>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsService::MyPinsService(IMyPinsRepository& myPinsRepository,
                                         MyPinsFileIO& myPinsFileIO,
                                         IMyPinSelectionHandlerFactory& myPinSelectionHandlerFactory,
                                         IMyPinVisibilityStateChangedHandlerFactory& myPinVisibilityStateChangedHandlerFactory,
                                         IMyPinBoundObjectFactory& myPinBoundObjectFactory,
                                         IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService)
                : m_myPinsRepository(myPinsRepository)
                , m_myPinsFileIO(myPinsFileIO)
                , m_myPinSelectionHandlerFactory(myPinSelectionHandlerFactory)
                , m_myPinVisibilityStateChangedHandlerFactory(myPinVisibilityStateChangedHandlerFactory)
                , m_myPinBoundObjectFactory(myPinBoundObjectFactory)
                , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
                , m_worldPinsService(worldPinsService)
                , m_lastIdUsed(m_myPinsFileIO.GetLastIdWrittenToDisk())
            {
            }
            
            void MyPinsService::LoadAllPinsFromDisk()
            {
                std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> > pinModelBindings;
                
                m_myPinsFileIO.LoadPinModelsFromDisk(pinModelBindings);
                
                for (std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> >::iterator it = pinModelBindings.begin();
                     it != pinModelBindings.end();
                     ++it)
                {
                    MyPinModel* pPinModel(it->first);
                    IMyPinBoundObject& pinModelBoundObject(*it->second);
                    
                    m_myPinBoundObjectRepository.AddBoundItemForPin(pPinModel->Identifier(), pinModelBoundObject);
                    pinModelBoundObject.HandlePinAdded(*pPinModel);
                    m_myPinsRepository.AddItem(pPinModel);
                    AddPinToMap(pPinModel);
                }
            }

            void MyPinsService::AddPinToMap(MyPinModel* pMyPinModel)
            {
                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(pMyPinModel->GetTitle(),
                                                                         pMyPinModel->GetDescription(),
                                                                         pMyPinModel->GetRatingsImage(),
                                                                         pMyPinModel->GetReviewsCount());
                
                MyPinSelectionHandler* pSelectionHandler(m_myPinSelectionHandlerFactory.CreateMyPinSelectionHandler(*pMyPinModel));
                
                WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* pVisibilityChangedHandler(m_myPinVisibilityStateChangedHandlerFactory.CreateMyPinVisibilityStateChangedHandler(*pMyPinModel));
                
                WorldPins::SdkModel::WorldPinItemModel* worldPinItemModel = m_worldPinsService.AddPin(pSelectionHandler,
                                                                                                      pVisibilityChangedHandler,
                                                                                                      worldPinFocusData,
                                                                                                      pMyPinModel->GetLatLong(),
                                                                                                      pMyPinModel->GetSdkMapPinIconIndexIcon());
                m_myPinToWorldPinMap.insert(std::make_pair(pMyPinModel, worldPinItemModel));
            }

            void MyPinsService::RemovePinWithId(const int myPinId)
            {
                for (TMyPinToWorldPinMap::iterator it = m_myPinToWorldPinMap.begin(); it != m_myPinToWorldPinMap.end(); ++it)
                {
                    MyPinModel* pinModel = it->first;
                    WorldPins::SdkModel::WorldPinItemModel* worldPinItemModel = it->second;

                    if (pinModel->Identifier() == myPinId)
                    {
                        IMyPinBoundObject& boundObject = m_myPinBoundObjectRepository.GetBoundObjectForPin(*pinModel);
                        m_myPinBoundObjectRepository.RemoveBoundItemForPin(pinModel->Identifier());
                        boundObject.HandlePinRemoved(*pinModel);
                        boundObject.HandlePinDestroyed(*pinModel);
                        Eegeo_DELETE &boundObject;
                        
                        m_worldPinsService.RemovePin(worldPinItemModel);
                        m_myPinsRepository.RemoveItem(pinModel);
                        m_myPinToWorldPinMap.erase(it);
                        break;
                    }
                }
            }
            
            void MyPinsService::SaveUserCreatedPoiPin(const std::string& title,
                                                      const std::string& description,
                                                      const std::string& ratingsImage,
                                                      const int reviewCount,
                                                      const Eegeo::Space::LatLong& latLong,
                                                      Byte* imageData,
                                                      size_t imageSize,
                                                      bool shouldShare)
            {
                MyPinModel::TPinIdType idForThisPin = ++m_lastIdUsed;
                const int myPinIconIndex = 9;
                
                IMyPinBoundObject& boundObject = *m_myPinBoundObjectFactory.CreateUserCreatedPinBoundObject(m_myPinsFileIO,
                                                                                                            idForThisPin,
                                                                                                            imageData,
                                                                                                            imageSize,
                                                                                                            shouldShare);
                m_myPinBoundObjectRepository.AddBoundItemForPin(idForThisPin, boundObject);
                
                MyPinModel *pinModel = Eegeo_NEW(MyPinModel)(MyPinModel::CurrentVersion,
                                                             idForThisPin,
                                                             title,
                                                             description,
                                                             ratingsImage,
                                                             reviewCount,
                                                             myPinIconIndex,
                                                             latLong);
                
                boundObject.HandlePinCreated(*pinModel);
                boundObject.HandlePinAdded(*pinModel);
                
                m_myPinsRepository.AddItem(pinModel);
                AddPinToMap(pinModel);
            }
            
            void MyPinsService::SaveSearchResultPoiPin(const Search::SdkModel::SearchResultModel& searchResult,
                                                       int pinIconIndex)
            {
                MyPinModel::TPinIdType idForThisPin = ++m_lastIdUsed;
                
                IMyPinBoundObject& boundObject = *m_myPinBoundObjectFactory.CreateSearchResultPinBoundObject(m_myPinsFileIO,
                                                                                                             idForThisPin,
                                                                                                             searchResult);
                m_myPinBoundObjectRepository.AddBoundItemForPin(idForThisPin, boundObject);
                
                // Use the ratings image if available, else fall back to address.
                const std::string& ratingsImage(searchResult.GetRatingImageUrl());
                                
                MyPinModel *pinModel = Eegeo_NEW(MyPinModel)(MyPinModel::CurrentVersion,
                                                             idForThisPin,
                                                             searchResult.GetTitle(),
                                                             searchResult.GetAddress(),
                                                             searchResult.GetRatingImageUrl(),
                                                             searchResult.GetReviewCount(),
                                                             pinIconIndex,
                                                             searchResult.GetLocation());
                
                boundObject.HandlePinCreated(*pinModel);
                boundObject.HandlePinAdded(*pinModel);
                
                m_myPinsRepository.AddItem(pinModel);
                AddPinToMap(pinModel);
            }
        }
    }
}
