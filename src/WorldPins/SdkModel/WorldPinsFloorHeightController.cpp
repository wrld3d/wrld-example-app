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
#include "IImmutableInteriorViewModel.h"

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
            WorldPinsFloorHeightController::WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                                                           Eegeo::Pins::PinRepository& pinRepository,
                                                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           const bool interiorsAffectedByFlattening,
                                                                           const bool useLabels)
                : m_worldPinsRepository(worldPinsRepository)
                , m_pinRepository(pinRepository)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorsAffectedByFlattening(interiorsAffectedByFlattening)
                , m_useLabels(useLabels)
            {
            }
            
            WorldPinsFloorHeightController::~WorldPinsFloorHeightController()
            {
            }
            
            
            
            void WorldPinsFloorHeightController::Update(float deltaSeconds)
            {
                if (!m_useLabels)
                {
                    UpdatePins(deltaSeconds);
                }
            }
            void WorldPinsFloorHeightController::UpdatePins(float deltaSeconds)
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
                            }
                        }
                    }
                }
            }
            
        }
    }
}
