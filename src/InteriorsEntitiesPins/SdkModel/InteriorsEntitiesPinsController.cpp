// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsController.h"
#include "PinRepository.h"
#include "InteriorsModel.h"
#include "InteriorsEntityModel.h"
#include "LatLongAltitude.h"
#include "Pin.h"
#include "MathsHelpers.h"
#include "PinController.h"
#include "InteriorsModelRepository.h"
#include "InteriorsEntityPinData.h"
#include "IInteriorsLabelController.h"
#include "InteriorsFloorModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorsEntitiesRepository.h"
#include "InteriorTransitionModel.h"
#include "StringHelpers.h"
#include "IWorldPinIconMapping.h"
#include "SerializedJsonHelpers.h"
#include "InteriorHelpers.h"
#include "InteriorsEntitiesHelpers.h"

#include <math.h>

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            InteriorsEntitiesPinsController::InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepostiory,
                                                                             Eegeo::Pins::PinController& pinController,
                                                                             Eegeo::Pins::PinRepository& pinRepository,
                                                                             const ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping& pinIconMapper,
                                                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                             const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                             Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyInteriorsLabelsController,
                                                                             const bool useLegacyInteriorLabels)
            : m_interiorsEntitiesRepository(interiorsEntitiesRepostiory)
            , m_pinController(pinController)
            , m_pinRepository(pinRepository)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_legacyInteriorsLabelsController(legacyInteriorsLabelsController)
            , m_useLegacyInteriorLabels(useLegacyInteriorLabels)
            , m_entitiesAddedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesAdded)
            , m_entitiesRemovedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesRemoved)
            , m_interiorModelChangedCallback(this, &InteriorsEntitiesPinsController::HandleInteriorModelChanged)
            , m_interiorInteractionStateChangedCallback(this, &InteriorsEntitiesPinsController::HandleInteriorInteractionStateChanged)
            , m_lastId(0)
            {
                m_interiorsEntitiesRepository.RegisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.RegisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorModelChangedCallback);
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_interiorInteractionStateChangedCallback);
                
                m_labelNameToIconIndex["restroom"] = pinIconMapper.IconIndexForKey(IconKeyToilets);
                m_labelNameToIconIndex["men's bathroom"] = pinIconMapper.IconIndexForKey(IconKeyToilets);
                m_labelNameToIconIndex["women's bathroom"] = pinIconMapper.IconIndexForKey(IconKeyToilets);
                m_labelNameToIconIndex["bathroom"] = pinIconMapper.IconIndexForKey(IconKeyToilets);
                m_labelNameToIconIndex["elevator"] = pinIconMapper.IconIndexForKey(IconKeyElevator);
                m_labelNameToIconIndex["escalator"] = pinIconMapper.IconIndexForKey(IconKeyEscalator);
                m_labelNameToIconIndex["stairs"] = pinIconMapper.IconIndexForKey(IconKeyStairs);
                
                if (m_useLegacyInteriorLabels)
                {
                    for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                    {
                        const std::string& labelName = it->first;
                        m_legacyInteriorsLabelsController.AddLabelToOmit(labelName);
                    }
                }
            }
            
            InteriorsEntitiesPinsController::~InteriorsEntitiesPinsController()
            {
                m_interiorsEntitiesRepository.UnregisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.UnregisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorModelChangedCallback);
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_interiorInteractionStateChangedCallback);
                
                if (m_useLegacyInteriorLabels)
                {
                    for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                    {
                        const std::string& labelName = it->first;
                        m_legacyInteriorsLabelsController.RemoveLabelToOmit(labelName);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::Update(float dt)
            {
                const float TransitionTimeInSeconds = 0.75f;
                
                if (m_interiorInteractionModel.HasInteriorModel() && m_interiorTransitionModel.InteriorIsVisible())
                {
                    UpdateScaleForPins(dt/TransitionTimeInSeconds);
                }
            }
            
            void InteriorsEntitiesPinsController::Event_TouchTap(const AppInterface::TapData& data)
            {
                // TODO: Support tapping labels in non-legacy mode.
                // TODO: Leaving this here in case we want to consume touch and be able to tap pins.
                std::vector<Eegeo::Pins::Pin*> intersectingPins;
                m_pinController.TryGetPinsIntersectingScreenPoint(data.point, intersectingPins);

                if (intersectingPins.size() > 0)
                {
                    m_interiorPinSelectedCallbacks.ExecuteCallbacks(intersectingPins);
                }
            }

            void InteriorsEntitiesPinsController::RegisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback)
            {
                m_interiorPinSelectedCallbacks.AddCallback(callback);
            }

            void InteriorsEntitiesPinsController::UnregisterInteriorsPinSelected(Eegeo::Helpers::ICallback1<const std::vector<Eegeo::Pins::Pin*>&>& callback)
            {
                m_interiorPinSelectedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsEntitiesPinsController::AddPinsForEntities(const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                Eegeo_ASSERT(m_interiorInteractionModel.HasInteriorModel());
                
                const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                
                for (Eegeo::Resources::Interiors::Entities::TEntityModelVector::const_iterator it = entities.begin(); it != entities.end(); ++it)
                {
                    const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata =
                            interiorModel.GetMetadataForEntityFromCategory("labels", (*it)->GetIdentifier());

                    if (pMetadata == NULL)
                    {
                        continue;
                    }
                    
                    const int iconIndex = FindPinIconIndexForEntity(*pMetadata);
                    if (iconIndex >= 0)
                    {
                        AddPinForEntity(**it, interiorModel);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::AddPinForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityModel& model, const Eegeo::Resources::Interiors::InteriorsModel& interiorModel)
            {
                Eegeo_ASSERT(m_entityToPinIdMap.find(&model) == m_entityToPinIdMap.end(), "Already has pin for model");
                
                const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata *pMetadata = interiorModel.GetMetadataForEntityFromCategory("labels", model.GetIdentifier());
                
                Eegeo_ASSERT(pMetadata != NULL, "No metadata to create entity pin");
                
                Eegeo::Space::LatLong pinLocation = Eegeo::Space::LatLong::FromDegrees(pMetadata->latitudeDegrees, pMetadata->longitudeDegrees);

                const int pinIconIndex = FindPinIconIndexForEntity(*pMetadata);
                Eegeo_ASSERT(pinIconIndex >= 0, "Wasn't expecting to generate a pin for this label");
                
                if (m_floorToScaleMap.find(pMetadata->floorNumber) == m_floorToScaleMap.end())
                {
                    m_floorToScaleMap[pMetadata->floorNumber] = 0.f;
                }

                Entities::InteriorsEntityPinData* pPinData = Eegeo_NEW(Entities::InteriorsEntityPinData)(pMetadata->floorNumber);
                Eegeo::Pins::Pin* pPin = Eegeo_NEW(Eegeo::Pins::Pin)(m_lastId, pinLocation, 0.0f, pinIconIndex, pPinData);
                
                float bottomOfInterior = m_interiorInteractionModel.GetInteriorModel()->GetTangentSpaceBounds().GetMin().y;
                float heightAboveGround = (pMetadata->altitude - bottomOfInterior) + Eegeo::Resources::Interiors::Entities::Helpers::GetHeightOffset(pMetadata);
                
                pPin->SetTerrainHeight(bottomOfInterior, 14);
                pPin->SetHeightAboveTerrain(heightAboveGround);

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

                Eegeo_ASSERT(m_interiorInteractionModel.HasInteriorModel(), "no current interior");
                
                const Eegeo::Resources::Interiors::InteriorsFloorModel& floorModel = *m_interiorInteractionModel.GetSelectedFloorModel();
                
                int currentFloorNumber = floorModel.GetFloorNumber();

                const bool canShowPins = m_interiorInteractionModel.IsCollapsed() && m_interiorTransitionModel.IsFadingInOrFullyVisible();
                
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
                if(!m_useLegacyInteriorLabels)
                {
                    return false;
                }
                
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
                    if(CanProcessEntities(interiorModel.GetName(), entities))
                    {
                        AddPinsForEntities(entities);
                    }
                }
                else
                {
                    RemoveAllPins();
                    m_floorToScaleMap.clear();
                }
            }
            
            int InteriorsEntitiesPinsController::FindPinIconIndexForEntity(const Eegeo::Resources::Interiors::Entities::InteriorsEntityMetadata& interiorsEntityMetadata) const
            {
                const std::string& nameLowerCase = Eegeo::Helpers::ToLower(interiorsEntityMetadata.name);
                
                std::map<std::string, int>::const_iterator iter = m_labelNameToIconIndex.find(nameLowerCase);
                
                if (iter == m_labelNameToIconIndex.end())
                {
                    return -1;
                }
                else
                {
                    return iter->second;
                }
            }
        }
    }
}
