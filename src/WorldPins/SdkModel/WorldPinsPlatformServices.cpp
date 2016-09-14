// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsPlatformServices.h"
#include "Hypodermic/ContainerBuilder.h"
#include "PinsModule.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsPlatformServices::WorldPinsPlatformServices(const std::shared_ptr<ExampleApp::WorldPins::SdkModel::IWorldPinIconMapping>& iconMapping,
                                      const std::shared_ptr<Eegeo::Modules::IPlatformAbstractionModule>& platformAbscrationModule,
                                      const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties,
                                      const std::shared_ptr<Eegeo::EegeoWorld>& world)
            : m_iconMapping(iconMapping)
            , m_platformAbscrationModule(platformAbscrationModule)
            , m_screenProperties(screenProperties)
            , m_world(world)
            {
                m_pinsModule = std::shared_ptr<Eegeo::Pins::PinsModule>(Eegeo::Pins::PinsModule::CreateWithAtlas(
                                                                                                                 m_world->GetRenderingModule(),
                                                                                                                 *m_platformAbscrationModule,
                                                                                                                 m_world->GetMapModule(),
                                                                                                                 m_iconMapping->GetTextureInfo().textureId,
                                                                                                                 m_iconMapping->GetTexturePageLayout(),
                                                                                                                 Eegeo::Rendering::LayerIds::InteriorEntities,
                                                                                                                 *m_screenProperties));
                m_pinsRepository = Hypodermic::makeExternallyOwned(m_pinsModule->GetRepository());
                m_pinsController = Hypodermic::makeExternallyOwned(m_pinsModule->GetController());
            }
            
            const std::shared_ptr<Eegeo::Pins::PinRepository>& WorldPinsPlatformServices::GetPinRepository() { return m_pinsRepository; }
            const std::shared_ptr<Eegeo::Pins::PinController>& WorldPinsPlatformServices::GetPinController() { return m_pinsController; }
            const std::shared_ptr<Eegeo::Pins::PinsModule>& WorldPinsPlatformServices::GetPinsModule() { return m_pinsModule; }
        }
    }
}
