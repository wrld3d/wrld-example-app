// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsEntitiesPinsController.h"
#include "Interiors.h"
#include "ICallback.h"
#include "Pins.h"
#include "AppInterface.h"
#include "GlobeCamera.h"
#include "InteriorsEntitiesRepository.h"
#include "Terrain.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            typedef std::map<const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel*, Eegeo::Pins::TPinId> TEntityToPinIdMap;
            
            enum InteriorViewState
            {
                NotViewing,
                Viewing,
                Exiting
            };
            
            class InteriorsEntitiesPinsController : public IInteriorsEntitiesPinsController
            {
            public:
                
                InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepository,
                                                Eegeo::Pins::PinController& pinController,
                                                Eegeo::Pins::PinRepository& pinRepository,
                                                Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& interiorsLabelsController,
                                                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
                
                ~InteriorsEntitiesPinsController();
                
                void Update(float dt);
                
                void Event_TouchTap(const AppInterface::TapData& data, Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController);
                
            private:
                void AddPinsForEntities(const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                void AddPinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model);
                void RemovePinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model);
                void RemoveAllPins();
                void UpdateScaleForPins(float t);
                
                Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& m_interiorsEntitiesRepository;
                Eegeo::Pins::PinController& m_pinController;
                Eegeo::Pins::PinRepository& m_pinRepository;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& m_interiorsLabelsController;
                
                Eegeo::Helpers::TCallback2<InteriorsEntitiesPinsController, const std::string&, const Eegeo::Resources::Interiors::Entities::TEntityModelVector&> m_entitiesAddedCallback;
                Eegeo::Helpers::TCallback2<InteriorsEntitiesPinsController, const std::string&, const Eegeo::Resources::Interiors::Entities::TEntityModelVector&> m_entitiesRemovedCallback;
                
                void OnEntitiesAdded(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                void OnEntitiesRemoved(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                
                Eegeo::Helpers::TCallback0<InteriorsEntitiesPinsController> m_interiorVisibilityChangedCallback;
                void OnInteriorVisibilityChanged();
                
                const Eegeo::Resources::Interiors::InteriorsModel* m_pCurrentInteriorsModel;
                
                std::map<std::string, int> m_labelNameToIconIndex;
                std::map<int, float> m_floorToScaleMap;
                TEntityToPinIdMap m_entityToPinIdMap;
                
                InteriorViewState m_interiorViewState;
                
                Eegeo::Pins::TPinId m_lastId;
                
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
            };
        }
    }
}