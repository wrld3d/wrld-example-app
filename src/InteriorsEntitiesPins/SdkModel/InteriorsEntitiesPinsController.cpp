// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsController.h"
#include "PinRepository.h"
#include "InteriorsModel.h"
#include "InteriorsEntityModel.h"
#include "LatLongAltitude.h"
#include "Pin.h"
#include "InteriorController.h"
#include "MathsHelpers.h"
#include "PinController.h"
#include "InteriorsModelRepository.h"
#include "InteriorsEntityPinData.h"
#include "IInteriorsLabelController.h"
#include "InteriorsFloorModel.h"
#include "TerrainHeightProvider.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            bool IsViewingInterior(const InteriorViewState& interiorViewState)
            {
                return interiorViewState == Viewing || interiorViewState == Exiting;
            }
            
            InteriorsEntitiesPinsController::InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepostiory,
                                                                             Eegeo::Pins::PinController& pinController,
                                                                             Eegeo::Pins::PinRepository& pinRepository,
                                                                             Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                             Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& interiorsLabelsController,
                                                                             Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
            : m_interiorsEntitiesRepository(interiorsEntitiesRepostiory)
            , m_pinController(pinController)
            , m_pinRepository(pinRepository)
            , m_interiorController(interiorController)
            , m_interiorsLabelsController(interiorsLabelsController)
            , m_entitiesAddedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesAdded)
            , m_entitiesRemovedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesRemoved)
            , m_interiorVisibilityChangedCallback(this, &InteriorsEntitiesPinsController::OnInteriorVisibilityChanged)
            , m_lastId(0)
            , m_pCurrentInteriorsModel(NULL)
            , m_interiorViewState(NotViewing)
            , m_terrainHeightProvider(terrainHeightProvider)
            {
                m_interiorsEntitiesRepository.RegisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.RegisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorController.RegisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
                
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
                
                m_interiorController.UnregisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
                
                for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                {
                    const std::string& labelName = it->first;
                    m_interiorsLabelsController.RemoveLabelToOmit(labelName);
                }
            }
            
            void InteriorsEntitiesPinsController::Update(float dt)
            {
                const float TransitionTimeInSeconds = 0.75f;
                
                if (IsViewingInterior(m_interiorViewState) && m_interiorController.InteriorIsVisible())
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
                for (Eegeo::Resources::Interiors::Entities::TEntityModelVector::const_iterator it = entities.begin(); it != entities.end(); ++it)
                {
                    const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata = m_pCurrentInteriorsModel->GetMetadataForEntityFromCategory("labels", (*it)->GetIdentifier());
                    if (pMetadata == NULL)
                    {
                        continue;
                    }
                    
                    if (m_labelNameToIconIndex.find(pMetadata->name) != m_labelNameToIconIndex.end())
                    {
                        AddPinForEntity(**it);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::AddPinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model)
            {
                Eegeo_ASSERT(m_pCurrentInteriorsModel != NULL, "Can't load entity pins without interior model");
                Eegeo_ASSERT(m_entityToPinIdMap.find(&model) == m_entityToPinIdMap.end(), "Already has pin for model");
                
                const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata = m_pCurrentInteriorsModel->GetMetadataForEntityFromCategory("labels", model.GetIdentifier());
                
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
                
                for (std::map<int, float>::iterator it = m_floorToScaleMap.begin(); it != m_floorToScaleMap.end(); ++it)
                {
                    const int floorNumber = it->first;
                    float scale = it->second;
                    float scaleDelta = floorNumber == currentFloorNumber && m_interiorViewState != Exiting ? t : -t;
                    
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
            
            void InteriorsEntitiesPinsController::OnEntitiesAdded(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                if (m_pCurrentInteriorsModel == NULL || interiorName != m_pCurrentInteriorsModel->GetName() || entities.empty())
                {
                    return;
                }
                
                AddPinsForEntities(entities);
            }
            
            void InteriorsEntitiesPinsController::OnEntitiesRemoved(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                if (m_pCurrentInteriorsModel == NULL || interiorName != m_pCurrentInteriorsModel->GetName() || entities.empty())
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
            
            void InteriorsEntitiesPinsController::OnInteriorVisibilityChanged()
            {
                if (m_interiorController.InteriorIsVisible())
                {
                    bool success = m_interiorController.TryGetCurrentModel(m_pCurrentInteriorsModel);
                    if (!success)
                    {
                        return;
                    }
                    
                    Eegeo_ASSERT(m_pCurrentInteriorsModel != NULL, "Have NULL interior model");
                    m_interiorViewState = Viewing;
                    
                    const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities = m_interiorsEntitiesRepository.GetAllStreamedEntitiesForInterior(m_pCurrentInteriorsModel->GetName());
                    AddPinsForEntities(entities);
                }
                else
                {
                    m_interiorViewState = NotViewing;
                    m_pCurrentInteriorsModel = NULL;
                    
                    RemoveAllPins();
                    m_floorToScaleMap.clear();
                }
            }
        }
    }
}