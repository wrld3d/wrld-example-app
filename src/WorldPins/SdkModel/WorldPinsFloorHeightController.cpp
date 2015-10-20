//  Copyright (c) 2015 eeGeo. All rights reserved.

#include "WorldPinsFloorHeightController.h"

#include "EarthConstants.h"
#include "IWorldPinsRepository.h"
#include "InteriorController.h"
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
                                                                           Eegeo::Resources::Interiors::InteriorController& interiorController)
                : m_worldPinsRepository(worldPinsRepository)
                , m_pinRepository(pinRepository)
                , m_interiorController(interiorController)
            {
            }
            
            WorldPinsFloorHeightController::~WorldPinsFloorHeightController()
            {
            }
            
            void WorldPinsFloorHeightController::Update(float deltaSeconds)
            {
                bool showingInterior = m_interiorController.InteriorIsVisible();
                if(showingInterior)
                {
                    const Eegeo::Resources::Interiors::InteriorsModel *pModel = NULL;
                    if (m_interiorController.TryGetCurrentModel(pModel))
                    {
                        const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                        if (m_interiorController.TryGetCurrentFloorModel(pFloorModel))
                        {
                            float floorHeightAboveSeaLevel = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(*pModel, m_interiorController.GetCurrentFloorIndex());
                            
                            for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
                            {
                                WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
                                if (worldPinItemModel.NeedsFloorHeight())
                                {
                                    if (worldPinItemModel.GetInteriorData().floor == m_interiorController.GetCurrentFloorIndex() &&
                                        worldPinItemModel.GetInteriorData().building == pModel->GetId())
                                    {
                                        Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(worldPinItemModel.Id());
                                        worldPinItemModel.SetFloorHeight(floorHeightAboveSeaLevel);
                                        // TODO: Change to new SetHeightAboveTerrain
                                        pPin->SetTerrainHeight(floorHeightAboveSeaLevel, 14);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}