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
#include "CallbackCollection.h"
#include "InteriorsEntityMetadata.h"
#include "WorldPins.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            typedef std::map<const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel*, Eegeo::Pins::TPinId> TEntityToPinIdMap;
            
            const std::string IconKeyToilets = "toilets";
            const std::string IconKeyEscalator = "escalator";
            const std::string IconKeyStairs = "stairs";
            const std::string IconKeyElevator = "elevator";
            
            class InteriorsEntitiesPinsController : public IInteriorsEntitiesPinsController
            {
            public:
                
                InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepository,
                                                Eegeo::Pins::PinController& pinController,
                                                Eegeo::Pins::PinRepository& pinRepository,
                                                const ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping& pinIconMapper,
                                                Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& interiorsLabelsController);
                
                ~InteriorsEntitiesPinsController();
                
                void Update(float dt);
                
                void Event_TouchTap(const AppInterface::TapData& data);

                void RegisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback);
                void UnregisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback);
                
            private:
                void AddPinsForEntities(const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                void AddPinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model, const Eegeo::Resources::Interiors::InteriorsModel& interiorModel);
                void RemovePinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model);
                void RemoveAllPins();
                void UpdateScaleForPins(float t);
                int FindPinIconIndexForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata& interiorsEntityMetadata) const;
                
                Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& m_interiorsEntitiesRepository;
                Eegeo::Pins::PinController& m_pinController;
                Eegeo::Pins::PinRepository& m_pinRepository;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& m_interiorsLabelsController;
                
                Eegeo::Helpers::TCallback2<InteriorsEntitiesPinsController, const std::string&, const Eegeo::Resources::Interiors::Entities::TEntityModelVector&> m_entitiesAddedCallback;
                Eegeo::Helpers::TCallback2<InteriorsEntitiesPinsController, const std::string&, const Eegeo::Resources::Interiors::Entities::TEntityModelVector&> m_entitiesRemovedCallback;
                
                bool CanProcessEntities(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities) const;
                void OnEntitiesAdded(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                void OnEntitiesRemoved(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities);
                
                Eegeo::Helpers::TCallback0<InteriorsEntitiesPinsController> m_interiorModelChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorsEntitiesPinsController> m_interiorInteractionStateChangedCallback;
                
                void HandleInteriorModelChanged();
                void HandleInteriorInteractionStateChanged();
                
                std::map<std::string, int> m_labelNameToIconIndex;
                std::map<int, float> m_floorToScaleMap;
                TEntityToPinIdMap m_entityToPinIdMap;

                Eegeo::Helpers::CallbackCollection1<const std::vector<Eegeo::Pins::Pin*>&> m_interiorPinSelectedCallbacks;
                
                Eegeo::Pins::TPinId m_lastId;
            };
        }
    }
}