// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinIconMapping.h"
#include "Types.h"
#include "GLHelpers.h"
#include "Rendering.h"
#include <string>
#include <map>
#include <vector>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinIconMapping : public IWorldPinIconMapping, private Eegeo::NonCopyable
            {
            public:
                WorldPinIconMapping(const std::string& defaultKey, 
                    const Eegeo::Helpers::GLHelpers::TextureInfo& texture,
                    const Eegeo::Rendering::AtlasTexturePageLayout* pAtlas,
                    const std::map<std::string, int>& keyToIconIndex);
                
                virtual ~WorldPinIconMapping();

                virtual const Eegeo::Rendering::AtlasTexturePageLayout& GetTexturePageLayout() const;
                virtual const Eegeo::Helpers::GLHelpers::TextureInfo& GetTextureInfo() const;
                
                virtual int IconIndexForKey(const std::string& key) const;
                
            private:
                const std::string m_defaultKey;
                const Eegeo::Helpers::GLHelpers::TextureInfo m_texturePage;
                const Eegeo::Rendering::AtlasTexturePageLayout* m_pTextureAtlas;
                const std::map<std::string, int> m_keyToIconIndex;
            };
        }
    }
}
