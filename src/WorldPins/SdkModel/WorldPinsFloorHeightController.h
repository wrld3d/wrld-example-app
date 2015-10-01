// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsController.h"
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
                Eegeo::Resources::Interiors::InteriorsController& m_interiorsController;
                
            public:
                WorldPinsFloorHeightController(IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               Eegeo::Resources::Interiors::InteriorsController& interiorsController);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
