// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsEntitiesPinsModule.h"
#include "Modules.h"
#include "WorldPins.h"
#include "Pins.h"
#include "GLHelpers.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            class InteriorsEntitiesPinsModule : public IInteriorsEntitiesPinsModule
            {
            public:
                InteriorsEntitiesPinsModule(Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule,
                                            Eegeo::Modules::Core::RenderingModule& renderingModule,
                                            Eegeo::Modules::Map::MapModule& mapModule,
                                            const WorldPins::SdkModel::IWorldPinIconMapping& worldPinIconMapping,
                                            const Eegeo::Rendering::ScreenProperties& screenProperties);
                
                ~InteriorsEntitiesPinsModule();
                
                IInteriorsEntitiesPinsController& GetInteriorsEntitiesPinsController();
                Eegeo::Pins::PinsModule& GetPinsModule();
            private:
                
                Eegeo::Pins::PinsModule* m_pEntityPinsModule;
                IInteriorsEntitiesPinsController* m_pInteriorsEntitiesPinsController;
                
                Eegeo::Helpers::GLHelpers::TextureInfo m_entityPinsTextureInfo;
                Eegeo::Rendering::ITexturePageLayout* m_pEntityPinIconsTexturePageLayout;
            };
        }
    }
}