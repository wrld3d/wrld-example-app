// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorController.h"
#include "IWorldPinsFloorHeightController.h"
#include "WorldPins.h"
#include "Pins.h"

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
                const bool m_interiorsAffectedByFlattening;
                
            public:
                WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               Eegeo::Resources::Interiors::InteriorController& interiorController,
                                               const bool interiorsAffectedByFlattening);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
