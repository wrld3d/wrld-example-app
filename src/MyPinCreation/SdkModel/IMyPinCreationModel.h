// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include "MyPinCreationStage.h"
#include "ICallback.h"
#include "VectorMathDecl.h"
#include "Types.h"
#include "LatLongAltitude.h"

#include <string>

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class IMyPinCreationModel
            {
            public:
                virtual ~IMyPinCreationModel() { }

                virtual const MyPinCreationStage& GetCreationStage() const = 0;
                virtual void SetCreationStage(MyPinCreationStage stage) = 0;

                virtual void SetLatLong(const Eegeo::Space::LatLong& position) = 0;
                virtual const Eegeo::Space::LatLong& GetLatLong() const = 0;
                virtual float GetTerrainHeight() const = 0;
                virtual void SetTerrainHeight(float height) = 0;
                virtual void SetHeightAboveTerrain(float heightAboveTerrain) = 0;
                virtual float GetHeightAboveTerrain() const = 0;
                virtual const Eegeo::dv3& GetPosition() = 0;
                virtual void SetInterior(bool interior) = 0;
                virtual void SetFloor(int floor) = 0;
                virtual void SetBuildingId(const Eegeo::Resources::Interiors::InteriorId& buildingId) = 0;
                virtual bool NeedsTerrainHeight() const = 0;

                virtual void SavePoi(const std::string& title,
                                     const std::string& description,
                                     const std::string& ratingsImage,
                                     const int reviewCount,
                                     Byte* imageData,
                                     size_t imageSize,
                                     bool shouldShare) = 0;

                virtual void InsertStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback) = 0;
                virtual void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback) = 0;
            };
        }
    }
}
