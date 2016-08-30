// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <utility>

#include "InteriorId.h"
#include "MyPins.h"
#include "IMyPinsService.h"
#include "WorldPins.h"
#include "Menu.h"
#include "Search.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsService : public IMyPinsService, private Eegeo::NonCopyable
            {
            public:
                MyPinsService(const std::shared_ptr<IMyPinsRepository>& myPinsRepository,
                              const std::shared_ptr<MyPinsFileIO>& myPinsFileIO,
                              const std::shared_ptr<IMyPinSelectionHandlerFactory>& myPinSelectionHandlerFactory,
                              const std::shared_ptr<IMyPinVisibilityStateChangedHandlerFactory>& myPinVisibilityStateChangedHandlerFactory,
                              const std::shared_ptr<IMyPinBoundObjectFactory>& myPinBoundObjectFactory,
                              const std::shared_ptr<IMyPinBoundObjectRepository>& myPinBoundObjectRepository,
                              const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService);
                
                void LoadAllPinsFromDisk();

                bool TryGetWorldPinItemModelForMyPin(const int myPinId,
                                                     ExampleApp::WorldPins::SdkModel::WorldPinItemModel*& out_pWorldPinItemModel) const;
                
                void RemovePinWithId(const int myPinId);
                
                void SaveUserCreatedPoiPin(const std::string& title,
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
                                           bool shouldShare);
                
                void SaveSearchResultPoiPin(const Search::SdkModel::SearchResultModel& searchResult,
                                            const std::string& pinIconKey);
                
                void UpdatePinWithResult(const int myPinId, const Search::SdkModel::SearchResultModel& result);
                
                void SaveAllPinsToDisk();
                
            private:
                const std::shared_ptr<IMyPinsRepository> m_myPinsRepository;
                const std::shared_ptr<MyPinsFileIO> m_myPinsFileIO;
                const std::shared_ptr<IMyPinSelectionHandlerFactory> m_myPinSelectionHandlerFactory;
                const std::shared_ptr<IMyPinVisibilityStateChangedHandlerFactory> m_myPinVisibilityStateChangedHandlerFactory;
                const std::shared_ptr<IMyPinBoundObjectFactory> m_myPinBoundObjectFactory;
                const std::shared_ptr<IMyPinBoundObjectRepository> m_myPinBoundObjectRepository;
                const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService> m_worldPinsService;

                MyPinModel::TPinIdType m_lastIdUsed;

                typedef std::map<int, std::pair<MyPinModel*, WorldPins::SdkModel::WorldPinItemModel*> > TMyPinToWorldPinMap;
                TMyPinToWorldPinMap m_myPinToWorldPinMap;

                void AddPinToMap(MyPinModel* pMyPinModel, int aditionalMask);

                void SubmitPinToWebService(const MyPinModel& myPinModel);

                MyPinModel* GetPinWithId(int pinId);
            };
        }
    }
}
