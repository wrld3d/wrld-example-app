// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>

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
            class MyPinsService : public IMyPinsService
            {
            public:
                MyPinsService(IMyPinsRepository& myPinsRepository,
                              MyPinsFileIO& myPinsFileIO,
                              IMyPinSelectionHandlerFactory& myPinSelectionHandlerFactory,
                              IMyPinVisibilityStateChangedHandlerFactory& myPinVisibilityStateChangedHandlerFactory,
                              IMyPinBoundObjectFactory& myPinBoundObjectFactory,
                              IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                              WorldPins::SdkModel::IWorldPinsService& worldPinsService);
                
                void LoadAllPinsFromDisk();

                void RemovePinWithId(const int myPinId);
                
                void SaveUserCreatedPoiPin(const std::string& title,
                                           const std::string& description,
                                           const std::string& ratingsImage,
                                           const int reviewCount,
                                           const Eegeo::Space::LatLong& latLong,
                                           Byte* imageData,
                                           size_t imageSize,
                                           bool shouldShare);
                
                void SaveSearchResultPoiPin(const Search::SdkModel::SearchResultModel& searchResult,
                                            int pinIconIndex);
                
            private:
                IMyPinsRepository& m_myPinsRepository;
                MyPinsFileIO& m_myPinsFileIO;
                IMyPinSelectionHandlerFactory& m_myPinSelectionHandlerFactory;
                IMyPinVisibilityStateChangedHandlerFactory& m_myPinVisibilityStateChangedHandlerFactory;
                IMyPinBoundObjectFactory& m_myPinBoundObjectFactory;
                IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;

                MyPinModel::TPinIdType m_lastIdUsed;

                typedef std::map<MyPinModel*, WorldPins::SdkModel::WorldPinItemModel*> TMyPinToWorldPinMap;
                TMyPinToWorldPinMap m_myPinToWorldPinMap;

                void AddPinToMap(MyPinModel* pMyPinModel);

                void SubmitPinToWebService(const MyPinModel& myPinModel);

                MyPinModel* GetPinWithId(int pinId);
            };
        }
    }
}
