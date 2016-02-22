// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinsFloorHeightController.h"
#include "WorldPins.h"
#include "Pins.h"
#include "Rendering.h"
#include "Interiors.h"

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
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                const bool m_interiorsAffectedByFlattening;
                
            public:
                WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                               const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService,
                                               const bool interiorsAffectedByFlattening);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
