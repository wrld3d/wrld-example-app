// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <memory>
#include "EegeoWorld.h"
#include "IPlatformAbstractionModule.h"
#include "ScreenProperties.h"
#include "IWorldPinIconMapping.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsPlatformServices : private Eegeo::NonCopyable
            {
            public:
                WorldPinsPlatformServices(const std::shared_ptr<ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping>& iconMapping,
                                          const std::shared_ptr<Eegeo::Modules::IPlatformAbstractionModule>& platformAbscrationModule,
                                          const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties,
                                          const std::shared_ptr<Eegeo::EegeoWorld>& world);
                
                const std::shared_ptr<Eegeo::Pins::PinRepository>& GetPinRepository();
                const std::shared_ptr<Eegeo::Pins::PinController>& GetPinController();
                const std::shared_ptr<Eegeo::Pins::PinsModule>& GetPinsModule();
                
            private:
                const std::shared_ptr<ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping> m_iconMapping;
                const std::shared_ptr<Eegeo::Modules::IPlatformAbstractionModule> m_platformAbscrationModule;
                const std::shared_ptr<Eegeo::Rendering::ScreenProperties> m_screenProperties;
                const std::shared_ptr<Eegeo::EegeoWorld> m_world;
                std::shared_ptr<Eegeo::Pins::PinsModule> m_pinsModule;
                std::shared_ptr<Eegeo::Pins::PinRepository> m_pinsRepository;
                std::shared_ptr<Eegeo::Pins::PinController> m_pinsController;
            };
            
            class InteriorPinsPlatformServices : public WorldPinsPlatformServices
            {
                using WorldPinsPlatformServices::WorldPinsPlatformServices;
            };
        }
    }
}