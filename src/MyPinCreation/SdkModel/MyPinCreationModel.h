// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "InteriorId.h"
#include "CallbackCollection.h"
#include "VectorMath.h"
#include "IPlatformAbstractionModule.h"
#include "IWorkPool.h"
#include "MyPins.h"

#include <vector>

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class MyPinCreationModel : public IMyPinCreationModel
            {
            public:
                MyPinCreationModel(MyPins::SdkModel::IMyPinsService& myPinsService);

                ~MyPinCreationModel();

                const MyPinCreationStage& GetCreationStage() const;
                void SetCreationStage(MyPinCreationStage stage);

                const Eegeo::dv3& GetPosition() const;
                float GetTerrainHeight() const;
                void SetPosition(const Eegeo::dv3& position);
                void SetTerrainHeight(float height);
                void SetHeightAboveTerrain(float heightAboveTerrain);
                void SetInterior(bool interior);
                void SetFloor(int floor);
                void SetBuildingId(const Eegeo::Resources::Interiors::InteriorId& buildingId);
                bool NeedsTerrainHeight() const;

                void SavePoi(const std::string& title,
                             const std::string& description,
                             const std::string& ratingsImage,
                             const int reviewCount,
                             Byte* imageData,
                             size_t imageSize,
                             bool shouldShare);

                void InsertStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback);
                void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback);

            private:
                void UpdatePosition();
                
            private:
                bool m_needsTerrainHeightUpdate;
                MyPinCreationStage m_stage;
                Eegeo::dv3 m_position;
                float m_terrainHeight;
                float m_heightAboveTerrainMetres;
                bool m_interior;
                int m_floor;
                Eegeo::Resources::Interiors::InteriorId m_buildingId;

                MyPins::SdkModel::IMyPinsService& m_myPinsService;

                Eegeo::Helpers::CallbackCollection1<MyPinCreationStage> m_stateChangedCallbacks;
            };
        }
    }
}
