// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsController.h"
#include "PinRepository.h"
#include "InteriorsModel.h"
#include "InteriorsEntityModel.h"
#include "LatLongAltitude.h"
#include "Pin.h"
#include "IInteriorController.h"
#include "MathsHelpers.h"
#include "PinController.h"
#include "InteriorsModelRepository.h"
#include "InteriorsEntityPinData.h"
#include "IInteriorsLabelController.h"
#include "InteriorsFloorModel.h"
#include "TerrainHeightProvider.h"
#include "InteriorInteractionModel.h"
#include "InteriorsEntitiesRepository.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            InteriorsEntitiesPinsController::InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepostiory,
                                                                             Eegeo::Pins::PinController& pinController,
                                                                             Eegeo::Pins::PinRepository& pinRepository,
                                                                             Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                             Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& interiorsLabelsController,
                                                                             Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
            : m_interiorsEntitiesRepository(interiorsEntitiesRepostiory)
            , m_pinController(pinController)
            , m_pinRepository(pinRepository)
            , m_interiorController(interiorController)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorsLabelsController(interiorsLabelsController)
            , m_entitiesAddedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesAdded)
            , m_entitiesRemovedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesRemoved)
            , m_interiorModelChangedCallback(this, &InteriorsEntitiesPinsController::HandleInteriorModelChanged)
            , m_interiorInteractionStateChangedCallback(this, &InteriorsEntitiesPinsController::HandleInteriorInteractionStateChanged)
            , m_lastId(0)
            , m_terrainHeightProvider(terrainHeightProvider)
            {
                m_interiorsEntitiesRepository.RegisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.RegisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorModelChangedCallback);
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_interiorInteractionStateChangedCallback);
                
                // This is same across all interiors right now. If we want different omissions per interior
                // then we'll need to do a bit of work.
                m_labelNameToIconIndex["Restroom"] = 0;
                m_labelNameToIconIndex["Men's Bathroom"] = 0;
                m_labelNameToIconIndex["Women's Bathroom"] = 0;
                m_labelNameToIconIndex["Bathroom"] = 0;
                m_labelNameToIconIndex["Elevator"] = 1; // Not really an elevator logo, just for testing
                m_labelNameToIconIndex["Escalator"] = 1;
                
                for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                {
                    const std::string& labelName = it->first;
                    m_interiorsLabelsController.AddLabelToOmit(labelName);
                }
            }
            
            InteriorsEntitiesPinsController::~InteriorsEntitiesPinsController()
            {
                m_interiorsEntitiesRepository.UnregisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.UnregisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorModelChangedCallback);
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_interiorInteractionStateChangedCallback);
                
                for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                {
                    const std::string& labelName = it->first;
                    m_interiorsLabelsController.RemoveLabelToOmit(labelName);
                }
            }
            
            void InteriorsEntitiesPinsController::Update(float dt)
            {
                const float TransitionTimeInSeconds = 0.75f;
                
                if (m_interiorInteractionModel.HasInteriorModel() && m_interiorController.InteriorIsVisible())
                {
                    UpdateScaleForPins(dt/TransitionTimeInSeconds);
                }
            }
            
            void InteriorsEntitiesPinsController::Event_TouchTap(const AppInterface::TapData& data, Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController)
            {
                // TODO: Leaving this here in case we want to consume touch and be able to tap pins.
            }
            
            void InteriorsEntitiesPinsController::AddPinsForEntities(const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                Eegeo_ASSERT(m_interiorInteractionModel.HasInteriorModel());
                
                const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                
                for (Eegeo::Resources::Interiors::Entities::TEntityModelVector::const_iterator it = entities.begin(); it != entities.end(); ++it)
                {
                    const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata = interiorModel.GetMetadataForEntityFromCategory("labels", (*it)->GetIdentifier());
                    if (pMetadata == NULL)
                    {
                        continue;
                    }
                    
                    if (m_labelNameToIconIndex.find(pMetadata->name) != m_labelNameToIconIndex.end())
                    {
                        AddPinForEntity(**it, interiorModel);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::AddPinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model, const Eegeo::Resources::Interiors::InteriorsModel& interiorModel)
            {
                Eegeo_ASSERT(m_entityToPinIdMap.find(&model) == m_entityToPinIdMap.end(), "Already has pin for model");
                
                const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata = interiorModel.GetMetadataForEntityFromCategory("labels", model.GetIdentifier());
                
                Eegeo_ASSERT(m_labelNameToIconIndex.find(pMetadata->name) != m_labelNameToIconIndex.end(), "Wasn't expecting to generate a pin for this label");
                Eegeo_ASSERT(pMetadata != NULL, "No metadata to create entity pin");
                
                Eegeo::Space::LatLong pinLocation = Eegeo::Space::LatLong::FromDegrees(pMetadata->latitudeDegrees, pMetadata->longitudeDegrees);
                const float wallHeight = 5.f;
                float terrainHeight = 0.f;
                m_terrainHeightProvider.TryGetHeight(pinLocation.ToECEF(), 12, terrainHeight);
                
                const float height = static_cast<float>(pMetadata->altitude - terrainHeight + wallHeight);
                
                int pinIconIndex = m_labelNameToIconIndex.at(pMetadata->name);
                
                if (m_floorToScaleMap.find(pMetadata->floorNumber) == m_floorToScaleMap.end())
                {
                    m_floorToScaleMap[pMetadata->floorNumber] = 0.f;
                }
                
                Entities::InteriorsEntityPinData* pPinData = Eegeo_NEW(Entities::InteriorsEntityPinData)(pMetadata->floorNumber);
                Eegeo::Pins::Pin* pPin = Eegeo_NEW(Eegeo::Pins::Pin)(m_lastId, pinLocation, height, pinIconIndex, pPinData);
                m_entityToPinIdMap[&model] = m_lastId;
                m_pinRepository.AddPin(*pPin);
                m_pinController.SetScaleForPin(*pPin, 0.f);
                
                m_lastId++;
            }
            
            void InteriorsEntitiesPinsController::RemovePinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model)
            {
                Eegeo_ASSERT(m_entityToPinIdMap.find(&model) != m_entityToPinIdMap.end(), "Has no pin for model");
                
                const Eegeo::Pins::TPinId id = m_entityToPinIdMap[&model];
                m_entityToPinIdMap.erase(&model);
                
                Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(id);
                m_pinRepository.RemovePin(*pPin);
                Eegeo_DELETE pPin;
            }
            
            void InteriorsEntitiesPinsController::RemoveAllPins()
            {
                for (TEntityToPinIdMap::iterator it = m_entityToPinIdMap.begin(); it != m_entityToPinIdMap.end(); ++it)
                {
                    const Eegeo::Pins::TPinId id = it->second;

                    Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(id);
                    m_pinRepository.RemovePin(*pPin);
                    Eegeo_DELETE pPin;
                }
                
                m_entityToPinIdMap.clear();
            }
            
            void InteriorsEntitiesPinsController::UpdateScaleForPins(float t)
            {
                std::map<int, float> easedfloorScales;

                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                Eegeo_ASSERT(m_interiorController.TryGetCurrentFloorModel(pFloorModel), "Failed to fetch current floor");
                int currentFloorNumber = pFloorModel->GetFloorNumber();

                const bool canShowPins = m_interiorInteractionModel.IsCollapsed();
                
                for (std::map<int, float>::iterator it = m_floorToScaleMap.begin(); it != m_floorToScaleMap.end(); ++it)
                {
                    const int floorNumber = it->first;
                    float scale = it->second;
                    float scaleDelta = floorNumber == currentFloorNumber && canShowPins ? t : -t;
                    
                    scale += scaleDelta;
                    m_floorToScaleMap[floorNumber] = Eegeo::Math::Clamp01(scale);
                    
                    float easedScale = Eegeo::Helpers::MathsHelpers::PennerQuadraticEaseIn(m_floorToScaleMap[floorNumber], 0, 1, 1);
                    easedfloorScales[floorNumber] = easedScale;
                }
                
                const int pinCount = m_pinRepository.GetNumOfPins();
                for(int i = 0; i < pinCount; ++i)
                {
                    Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinAtIndex(i);
                    const Entities::InteriorsEntityPinData* pPinData = static_cast<const Entities::InteriorsEntityPinData*>(pPin->GetUserData());
                    m_pinController.SetScaleForPin(*pPin, easedfloorScales[pPinData->GetFloorNumber()]);
                }
            }
            
            bool InteriorsEntitiesPinsController::CanProcessEntities(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities) const
            {
                if (!m_interiorInteractionModel.HasInteriorModel())
                {
                    return false;
                }
                
                if (entities.empty())
                {
                    return false;
                }
                
                const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                
                if (interiorModel.GetName() != interiorName)
                {
                    return false;
                }
                
                return true;
            }
            
            
            
            void InteriorsEntitiesPinsController::OnEntitiesAdded(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                if (!CanProcessEntities(interiorName, entities))
                {
                    return;
                }
                
                AddPinsForEntities(entities);
            }
            
            void InteriorsEntitiesPinsController::OnEntitiesRemoved(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                if (!CanProcessEntities(interiorName, entities))
                {
                    return;
                }
                
                for (Eegeo::Resources::Interiors::Entities::TEntityModelVector::const_iterator it = entities.begin(); it != entities.end(); ++it)
                {
                    if (m_entityToPinIdMap.find(*it) != m_entityToPinIdMap.end())
                    {
                        RemovePinForEntity(**it);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::HandleInteriorInteractionStateChanged()
            {
                
            }
            
            void InteriorsEntitiesPinsController::HandleInteriorModelChanged()
            {
                if (m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                    
                    const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities = m_interiorsEntitiesRepository.GetAllStreamedEntitiesForInterior(interiorModel.GetName());
                    AddPinsForEntities(entities);
                }
                else
                {
                    RemoveAllPins();
                    m_floorToScaleMap.clear();
                }
            }
        }
    }
}