// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinsFloorHeightController.h"
#include "WorldPins.h"
#include "Pins.h"
#include "Rendering.h"
#include "Interiors.h"
#include "PlatformConfig.h"
#include <memory>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsFloorHeightController : public IWorldPinsFloorHeightController, private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IWorldPinsRepository>& m_worldPinsRepository;
                const std::shared_ptr<Eegeo::Pins::PinRepository>& m_pinRepository;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& m_interiorInteractionModel;
                const bool m_interiorsAffectedByFlattening;
                
            public:
                WorldPinsFloorHeightController(const std::shared_ptr<IWorldPinsRepository>& worldPinsRepository,
                                               const std::shared_ptr<Eegeo::Pins::PinRepository>& pinRepository,
                                               const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                               const std::shared_ptr<Eegeo::Config::PlatformConfig>& platformConfig);
                
                ~WorldPinsFloorHeightController();
                
                void Update(float deltaSeconds);
            };
        }
    }
}
