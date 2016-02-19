//  Copyright (c) 2015 eeGeo. All rights reserved.

#include "WorldPinsFloorHeightController.h"

#include "EarthConstants.h"
#include "IWorldPinsRepository.h"
#include "IInteriorController.h"
#include "InteriorInteractionModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorsModel.h"
#include "PinRepository.h"
#include "Pin.h"

#include "InteriorHeightHelpers.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsFloorHeightController::WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                                                           Eegeo::Pins::PinRepository& pinRepository,
                                                                           const Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                                                           Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                           const bool interiorsAffectedByFlattening)
                : m_worldPinsRepository(worldPinsRepository)
                , m_pinRepository(pinRepository)
                , m_interiorController(interiorController)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_environmentFlatteningService(environmentFlatteningService)
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
                    
                    float altitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(interiorModel, selectedFloorIndex);
                    float heightAboveTerrain = Helpers::InteriorHeightHelpers::INTERIOR_FLOOR_HEIGHT*selectedFloorIndex;
                    
                    for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                    {
                        WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
                        if (worldPinItemModel.NeedsFloorHeight())
                        {
                            if (worldPinItemModel.GetInteriorData().floor == selectedFloorIndex &&
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