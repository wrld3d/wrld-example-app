// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsController.h"
#include "PinRepository.h"
#include "InteriorsModel.h"
#include "InteriorsEntityModel.h"
#include "LatLongAltitude.h"
#include "Pin.h"
#include "InteriorsController.h"
#include "MathsHelpers.h"
#include "PinController.h"
#include "InteriorsModelRepository.h"
#include "InteriorsEntityPinData.h"
#include "InteriorsLabelController.h"

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
            
            InteriorsEntitiesPinsController::InteriorsEntitiesPinsController(Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                             Eegeo::Resources::Interiors::Entities::InteriorsEntitiesRepository& interiorsEntitiesRepostiory,
                                                                             Eegeo::Pins::PinController& pinController,
                                                                             Eegeo::Pins::PinRepository& pinRepository,
                                                                             Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                                             Eegeo::Resources::Interiors::Entities::InteriorsLabelsController& interiorsLabelsController)
            : m_interiorsModelRepository(interiorsModelRepository)
            , m_interiorsEntitiesRepository(interiorsEntitiesRepostiory)
            , m_pinController(pinController)
            , m_pinRepository(pinRepository)
            , m_interiorsController(interiorsController)
            , m_interiorsLabelsController(interiorsLabelsController)
            , m_entitiesAddedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesAdded)
            , m_entitiesRemovedCallback(this, &InteriorsEntitiesPinsController::OnEntitiesRemoved)
            , m_modelAddedCallback(this, &InteriorsEntitiesPinsController::OnModelAdded)
            , m_onExitInteriorCallback(this, &InteriorsEntitiesPinsController::OnInteriorExit)
            , m_showInteriorsStateChangedCallback(this, &InteriorsEntitiesPinsController::OnShowInteriorStateChanged)
            , m_lastId(0)
            , m_pCurrentInteriorsModel(NULL)
            , m_interiorViewState(NotViewing)
            {
                m_interiorsEntitiesRepository.RegisterEntitiesAddedCallback(m_entitiesAddedCallback);
                m_interiorsEntitiesRepository.RegisterEntitiesRemovedCallback(m_entitiesRemovedCallback);
                
                m_interiorsModelRepository.RegisterAddedCallback(m_modelAddedCallback);
                
                m_interiorsController.RegisterStateChangedCallback(m_showInteriorsStateChangedCallback);
                m_interiorsController.RegisterExitCallback(m_onExitInteriorCallback);
                
                m_labelNameToIconIndex["Restroom"] = 0;
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
                m_interiorsModelRepository.UnregisterAddedCallback(m_modelAddedCallback);
                
                m_interiorsController.UnregisterInteriorViewChangedCallback(m_showInteriorsStateChangedCallback);
                m_interiorsController.UnregisterExitCallback(m_onExitInteriorCallback);
                
                for (std::map<std::string, int>::const_iterator it = m_labelNameToIconIndex.begin(); it != m_labelNameToIconIndex.end(); ++it)
                {
                    const std::string& labelName = it->first;
                    m_interiorsLabelsController.RemoveLabelToOmit(labelName);
                }
            }
            
            void InteriorsEntitiesPinsController::Update(float dt)
            {
                const float TransitionTimeInSeconds = 0.75f;
                
                if (IsViewingInterior(m_interiorViewState) && m_interiorsController.GetExteriorMeshHasFaded())
                {
                    UpdateScaleForPins(dt/TransitionTimeInSeconds);
                }
            }
            
            void InteriorsEntitiesPinsController::Event_TouchTap(const AppInterface::TapData& data, Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController)
            {
                // TODO: Leaving this here in case we want to consume touch and be able to tap pins.
            }
            
            void InteriorsEntitiesPinsController::OnModelAdded(Eegeo::Resources::Interiors::InteriorsModel& model)
            {
                // Same as labels for now. This will change when we have multiple interiors.
                m_pCurrentInteriorsModel = &model;
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
                const float height = wallHeight * (pMetadata->floorNumber + 1);
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
                
                if (m_pinRepository.GetNumOfPins() == 0)
                {
                    m_floorToScaleMap.clear();
                }
            }
            
            void InteriorsEntitiesPinsController::UpdateScaleForPins(float t)
            {
                std::map<int, float> easedfloorScales;
                
                for (std::map<int, float>::iterator it = m_floorToScaleMap.begin(); it != m_floorToScaleMap.end(); ++it)
                {
                    const int floorNumber = it->first;
                    float scale = it->second;
                    float scaleDelta = floorNumber == m_interiorsController.GetCurrentFloorNumber() && m_interiorViewState != Exiting ? t : -t;
                    
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
            
            void InteriorsEntitiesPinsController::OnEntitiesRemoved(const std::string& interiorName, const Eegeo::Resources::Interiors::Entities::TEntityModelVector& entities)
            {
                for (Eegeo::Resources::Interiors::Entities::TEntityModelVector::const_iterator it = entities.begin(); it != entities.end(); ++it)
                {
                    if (m_entityToPinIdMap.find(*it) != m_entityToPinIdMap.end())
                    {
                        RemovePinForEntity(**it);
                    }
                }
            }
            
            void InteriorsEntitiesPinsController::OnInteriorExit()
            {
                m_interiorViewState = Exiting;
            }
            
            void InteriorsEntitiesPinsController::OnShowInteriorStateChanged()
            {
                m_interiorViewState = m_interiorsController.ShowingInterior() ? Viewing : NotViewing;
            }
        }
        
    }
}