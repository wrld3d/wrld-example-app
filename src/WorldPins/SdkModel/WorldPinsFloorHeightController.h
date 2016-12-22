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
                
                void UpdatePins(float deltaSeconds);
                
                IWorldPinsRepository& m_worldPinsRepository;
                Eegeo::Pins::PinRepository& m_pinRepository;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const bool m_interiorsAffectedByFlattening;
                float m_useLabels;
                
            public:
                WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                               const bool interiorsAffectedByFlattening,
                                               const bool useLabels);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
