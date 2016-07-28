// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "GLHelpers.h"
#include "AtlasTexturePageLayout.h"
#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinIconMapping
            {
            public:
                virtual ~IWorldPinIconMapping() { }

                virtual int IconIndexForKey(const std::string& key) const = 0;
                virtual const Eegeo::Rendering::AtlasTexturePageLayout& GetTexturePageLayout() const = 0;
                virtual const Eegeo::Helpers::GLHelpers::TextureInfo& GetTextureInfo() const = 0;
            };
        }
    }
}
