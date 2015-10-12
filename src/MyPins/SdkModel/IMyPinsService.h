// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include "MyPins.h"
#include "MyPinModel.h"
#include "Space.h"
#include "VectorMath.h"
#include "Types.h"
#include "Search.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinsService
            {
            public:
                virtual ~IMyPinsService() {}
                
                virtual void LoadAllPinsFromDisk() = 0;
                
                virtual bool TryGetWorldPinItemModelForMyPin(const int myPinId,
                                                             ExampleApp::WorldPins::SdkModel::WorldPinItemModel*& out_pWorldPinItemModel) const = 0;

                virtual void RemovePinWithId(const int myPinId) = 0;

                virtual void SaveUserCreatedPoiPin(const std::string& title,
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
                                                   bool shouldShare) = 0;
                
                
                virtual void SaveSearchResultPoiPin(const Search::SdkModel::SearchResultModel& searchResult,
                                                    int pinIconIndex) = 0;
                
                virtual void UpdatePinWithResult(const int myPinId, const Search::SdkModel::SearchResultModel& result) = 0;
            };
        }
    }
}
