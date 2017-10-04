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
#include "WorldPinVisibility.h"
#include "SearchVendorNames.h"
#include "YelpParsingHelpers.h"

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
                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinsRepository(myPinsRepository)
                , m_myPinsFileIO(myPinsFileIO)
                , m_myPinSelectionHandlerFactory(myPinSelectionHandlerFactory)
                , m_myPinVisibilityStateChangedHandlerFactory(myPinVisibilityStateChangedHandlerFactory)
                , m_myPinBoundObjectFactory(myPinBoundObjectFactory)
                , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
                , m_worldPinsService(worldPinsService)
                , m_lastIdUsed(m_myPinsFileIO.GetLastIdWrittenToDisk())
                , m_onMenuPinItemSelected(this, &MyPinsService::OnMenuPinItemSelected)
                , m_messageBus(messageBus)
            {
                m_messageBus.SubscribeNative(m_onMenuPinItemSelected);
            }

            MyPinsService::~MyPinsService()
            {
                m_messageBus.UnsubscribeNative(m_onMenuPinItemSelected);
            }
            
            void MyPinsService::LoadAllPinsFromDisk()
            {
                std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> > pinModelBindings;
                
                m_myPinsFileIO.LoadPinModelsFromDisk(pinModelBindings, *this);
                m_lastIdUsed = m_myPinsFileIO.GetLastIdWrittenToDisk();
                
                for (std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> >::iterator it = pinModelBindings.begin();
                     it != pinModelBindings.end();
                     ++it)
                {
                    MyPinModel* pPinModel(it->first);
                    IMyPinBoundObject& pinModelBoundObject(*it->second);
                    
                    m_myPinBoundObjectRepository.AddBoundItemForPin(pPinModel->Identifier(), pinModelBoundObject);
                    pinModelBoundObject.HandlePinAdded(*pPinModel);
                    m_myPinsRepository.AddItem(pPinModel);
                    AddPinToMap(pPinModel, WorldPins::SdkModel::WorldPinVisibility::None);
                }
            }

            void MyPinsService::AddPinToMap(MyPinModel* pMyPinModel, int aditionalMask)
            {
                const int priorityOrder = static_cast<int>(m_myPinsRepository.GetItemCount());
                
                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(pMyPinModel->GetTitle(),
                                                                         pMyPinModel->GetDescription(),
                                                                         pMyPinModel->GetVendor(),
                                                                         "",
                                                                         pMyPinModel->GetRatingsImage(),
                                                                         pMyPinModel->GetReviewsCount(),
                                                                         priorityOrder);
                
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(pMyPinModel->GetBuildingId(), pMyPinModel->GetFloor());
                
                MyPinSelectionHandler* pSelectionHandler(m_myPinSelectionHandlerFactory.CreateMyPinSelectionHandler(*pMyPinModel));
                
                WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* pVisibilityChangedHandler(m_myPinVisibilityStateChangedHandlerFactory.CreateMyPinVisibilityStateChangedHandler(*pMyPinModel));
                
                int pinVisibilityMask = WorldPins::SdkModel::WorldPinVisibility::UserPin | aditionalMask;
                
                WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = m_worldPinsService.AddPin(pSelectionHandler,
                                                                                                      pVisibilityChangedHandler,
                                                                                                      worldPinFocusData,
                                                                                                      pMyPinModel->IsInterior(),
                                                                                                      worldPinInteriorData,
                                                                                                      pMyPinModel->GetLatLong(),
                                                                                                      pMyPinModel->GetPinIconKey(),
                                                                                                      pMyPinModel->GetHeightAboveTerrainMetres(),
                                                                                                      pinVisibilityMask,
                                                                                                      pMyPinModel->GetTitle());

                m_myPinToWorldPinMap[pMyPinModel->Identifier()] = std::make_pair(pMyPinModel, pWorldPinItemModel);
            }
        
            bool MyPinsService::TryGetWorldPinItemModelForMyPin(const int myPinId,
                                                                ExampleApp::WorldPins::SdkModel::WorldPinItemModel*& out_pWorldPinItemModel) const
            {
                TMyPinToWorldPinMap::const_iterator it = m_myPinToWorldPinMap.find(myPinId);
                if(it != m_myPinToWorldPinMap.end())
                {
                    out_pWorldPinItemModel = it->second.second;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            void MyPinsService::RemovePinWithId(const int myPinId)
            {
                TMyPinToWorldPinMap::iterator it = m_myPinToWorldPinMap.find(myPinId);
                if(it != m_myPinToWorldPinMap.end())
                {
                    
                    MyPinModel* pPinModel = it->second.first;
                    WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = it->second.second;
                    m_worldPinsService.RemovePin(pWorldPinItemModel);

                    IMyPinBoundObject& boundObject = m_myPinBoundObjectRepository.GetBoundObjectForPin(*pPinModel);
                    m_myPinBoundObjectRepository.RemoveBoundItemForPin(pPinModel->Identifier());
                    boundObject.HandlePinRemoved(*pPinModel);
                    boundObject.HandlePinDestroyed(*pPinModel);
                    Eegeo_DELETE &boundObject;
                        
                    m_myPinsRepository.RemoveItem(pPinModel);
                    m_myPinToWorldPinMap.erase(it);
                }
            }

            void MyPinsService::RemoveAllPins()
            {
                std::vector<int> pinIDs;

                for (int pinIndex = 0; pinIndex < m_myPinsRepository.GetItemCount(); ++pinIndex)
                {
                    MyPinModel* pinAtIndex = m_myPinsRepository.GetItemAtIndex(pinIndex);
                    int pinID = pinAtIndex->Identifier();
                    pinIDs.push_back(pinID);
                }

                for (int i = 0; i < pinIDs.size(); i++)
                {
                    RemovePinWithId(pinIDs.at(i));
                }
            }

            void MyPinsService::UpdatePinWithResult(const int myPinId, const Search::SdkModel::SearchResultModel& result)
            {
                TMyPinToWorldPinMap::iterator it = m_myPinToWorldPinMap.find(myPinId);
                if(it != m_myPinToWorldPinMap.end())
                {
                    
                    MyPinModel* pPinModel = it->second.first;
                    WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = it->second.second;
                    std::string ratingImageUrl = "";
                    int reviewCount = 0;
                        
                    Search::Yelp::SdkModel::Helpers::TryParseReviewDetails(result, ratingImageUrl, reviewCount);
                        
                    pPinModel->Update(result.GetTitle(), result.GetSubtitle(), ratingImageUrl, reviewCount);
                    pWorldPinItemModel->Refresh(result.GetTitle(), result.GetSubtitle(), ratingImageUrl, reviewCount);
                        
                    SaveAllPinsToDisk();
                }
            }
            
            void MyPinsService::SaveAllPinsToDisk()
            {
                std::vector<MyPinModel*> pinModels;
                pinModels.reserve(m_myPinsRepository.GetItemCount());
                
                for (int i = 0; i < m_myPinsRepository.GetItemCount(); ++i)
                {
                    pinModels.push_back(m_myPinsRepository.GetItemAtIndex(i));
                }
                
                m_myPinsFileIO.SaveAllRepositoryPinsToDisk(pinModels);
            }
            
            void MyPinsService::SaveUserCreatedPoiPin(const std::string& title,
                                                      const std::string& description,
                                                      const std::string& ratingsImage,
                                                      const int reviewCount,
                                                      const Eegeo::Space::LatLong& latLong,
                                                      float heightAboveTerrainMetres,
                                                      bool interior,
                                                      const Eegeo::Resources::Interiors::InteriorId& buildingId,
                                                      int floor,
                                                      Byte* imageData,
                                                      size_t imageSize,
                                                      bool shouldShare)
            {
                MyPinModel::TPinIdType idForThisPin = ++m_lastIdUsed;
                const std::string pinIconKey = "my_location";
                
                IMyPinBoundObject& boundObject = *m_myPinBoundObjectFactory.CreateUserCreatedPinBoundObject(m_myPinsFileIO,
                                                                                                            idForThisPin,
                                                                                                            imageData,
                                                                                                            imageSize,
                                                                                                            shouldShare,
                                                                                                            pinIconKey);
                m_myPinBoundObjectRepository.AddBoundItemForPin(idForThisPin, boundObject);
                
                MyPinModel *pinModel = Eegeo_NEW(MyPinModel)(MyPinModel::CurrentVersion,
                                                             idForThisPin,
                                                             title,
                                                             description,
                                                             Search::MyPinVendorName,
                                                             ratingsImage,
                                                             pinIconKey,
                                                             reviewCount,
                                                             latLong,
                                                             heightAboveTerrainMetres,
                                                             interior,
                                                             buildingId,
                                                             floor);
                
                boundObject.HandlePinCreated(*pinModel);
                boundObject.HandlePinAdded(*pinModel);
                
                m_myPinsRepository.AddItem(pinModel);
                AddPinToMap(pinModel, WorldPins::SdkModel::WorldPinVisibility::None);
            }
            
            void MyPinsService::SaveSearchResultPoiPin(const Search::SdkModel::SearchResultModel& searchResult,
                                                       const std::string& pinIconKey)
            {
                
                
                MyPinModel::TPinIdType idForThisPin = ++m_lastIdUsed;
                
                IMyPinBoundObject& boundObject = *m_myPinBoundObjectFactory.CreateSearchResultPinBoundObject(m_myPinsFileIO,
                                                                                                             idForThisPin,
                                                                                                             searchResult,
                                                                                                             pinIconKey,
                                                                                                             *this);
                m_myPinBoundObjectRepository.AddBoundItemForPin(idForThisPin, boundObject);
                
                
                std::string ratingImageUrl = "";
                int reviewCount = 0;
                
                Search::Yelp::SdkModel::Helpers::TryParseReviewDetails(searchResult, ratingImageUrl, reviewCount);
                
                MyPinModel *pinModel = Eegeo_NEW(MyPinModel)(MyPinModel::CurrentVersion,
                                                             idForThisPin,
                                                             searchResult.GetTitle(),
                                                             searchResult.GetSubtitle(),
                                                             searchResult.GetVendor(),
                                                             ratingImageUrl,
                                                             pinIconKey,
                                                             reviewCount,
                                                             searchResult.GetLocation(),
                                                             searchResult.GetHeightAboveTerrainMetres(),
                                                             searchResult.IsInterior(),
                                                             searchResult.GetBuildingId(),
                                                             searchResult.GetFloor());
                
                boundObject.HandlePinCreated(*pinModel);
                boundObject.HandlePinAdded(*pinModel);
                
                m_myPinsRepository.AddItem(pinModel);
                AddPinToMap(pinModel, WorldPins::SdkModel::WorldPinVisibility::Search);
                m_worldPinsService.HighlightPin(m_myPinToWorldPinMap[pinModel->Identifier()].second, "selected_highlight_faded_in");
            }

            void MyPinsService::OnMenuPinItemSelected(const MyPinSelectedMessage& message)
            {
                int pinId = message.GetPinId();

                WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = NULL;

                TryGetWorldPinItemModelForMyPin(pinId, pWorldPinItemModel);

                m_worldPinsService.HighlightPin(pWorldPinItemModel);
            }
        }
    }
}
