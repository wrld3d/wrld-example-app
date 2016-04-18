//  Copyright (c) 2015 eeGeo. All rights reserved.

#include "WorldPinsFloorHeightController.h"

#include "EarthConstants.h"
#include "IWorldPinsRepository.h"
#include "InteriorInteractionModel.h"
#include "IInteriorFloorAnimator.h"
#include "InteriorsFloorModel.h"
#include "InteriorsModel.h"
#include "PinRepository.h"
#include "Pin.h"
#include "MathFunc.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorHelpers.h"
#include "InteriorViewModel.h"
#include "InteriorHeightHelpers.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            
            namespace
            {
                float CalculateAlphaForPin(int pinFloor, int selectedFloor, float floorParam, float expandedParam)
                {
                    const float expandedModePinFadeFloorRange = 2.5f;
                    float expandedAlpha = 1.0f - Eegeo::Math::Clamp01(Eegeo::Math::Abs((floorParam - pinFloor)/expandedModePinFadeFloorRange));
                    float collapsedAlpha = pinFloor == selectedFloor ? 1.0f : 0.0f;
                    return Eegeo::Math::Lerp(collapsedAlpha, expandedAlpha, expandedParam);
                }
            }
            
            WorldPinsFloorHeightController::WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                                                           Eegeo::Pins::PinRepository& pinRepository,
                                                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           const Eegeo::Resources::Interiors::IImmutableInteriorViewModel& interiorViewModel,
                                                                           const bool interiorsAffectedByFlattening)
                : m_worldPinsRepository(worldPinsRepository)
                , m_pinRepository(pinRepository)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorViewModel(interiorViewModel)
                , m_interiorsAffectedByFlattening(interiorsAffectedByFlattening)
            {
            }
            
            WorldPinsFloorHeightController::~WorldPinsFloorHeightController()
            {
            }
            
            void WorldPinsFloorHeightController::Update(float deltaSeconds)
            {
                if (m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                    const int selectedFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    
                    for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                    {
                        WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
                        if (worldPinItemModel.NeedsFloorHeight())
                        {
                            int pinFloorIndex = worldPinItemModel.GetInteriorData().floor;
                            
                            float altitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(interiorModel, pinFloorIndex);
                            float heightAboveTerrain = Helpers::InteriorHeightHelpers::INTERIOR_FLOOR_HEIGHT*pinFloorIndex;
                            if ((!m_interiorInteractionModel.IsCollapsed() || pinFloorIndex == selectedFloorIndex) &&
                                worldPinItemModel.GetInteriorData().building == interiorModel.GetId())
                            {
                                Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(worldPinItemModel.Id());
                                if(m_interiorsAffectedByFlattening)
                                {
                                    pPin->SetTerrainHeight(altitude, 14);
                                    pPin->SetHeightAboveTerrain(0.0f);
                                }
                                else
                                {
                                    pPin->SetTerrainHeight(interiorModel.GetTangentSpaceBounds().GetMin().y, 14);
                                    pPin->SetHeightAboveTerrain(heightAboveTerrain);
                                }
                                
                                if (m_interiorViewModel.IsValidFloorIndex(pinFloorIndex))
                                {
                                    Eegeo::Resources::Interiors::AttachPinToFloor(*pPin, pinFloorIndex, m_interiorViewModel);
                                }
                                
                                float alpha = CalculateAlphaForPin(pinFloorIndex, selectedFloorIndex, m_interiorInteractionModel.GetFloorParam(), m_interiorInteractionModel.GetExpandedParam());
                                pPin->SetColor(Eegeo::v4(1.0f, 1.0f, 1.0f, alpha));
                            }
                        }
                    }
                }
            }
            
        }
    }
}
