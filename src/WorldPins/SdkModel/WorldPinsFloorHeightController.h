// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsController.h"
#include "IWorldPinsFloorHeightController.h"
#include "WorldPins.h"
#include "Pins.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsFloorHeightController : public IWorldPinsFloorHeightController, private Eegeo::NonCopyable
            {
            private:
                IWorldPinsRepository& m_worldPinsRepository;
                Eegeo::Pins::PinRepository& m_pinRepository;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                const bool m_interiorsAffectedByFlattening;
                
            public:
                WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               Eegeo::Resources::Interiors::InteriorController& interiorController,
                                               const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService,
                                               const bool interiorsAffectedByFlattening);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
