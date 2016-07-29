// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinIconMapping.h"
#include "AtlasTexturePageLayout.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            
            WorldPinIconMapping::WorldPinIconMapping(const std::string& defaultKey,
                const Eegeo::Helpers::GLHelpers::TextureInfo& texture,
                const Eegeo::Rendering::AtlasTexturePageLayout* pAtlas,
                const std::map<std::string, int>& keyToIconIndex)
            : m_defaultKey(defaultKey)
            , m_texturePage(texture)
            , m_pTextureAtlas(pAtlas)
            , m_keyToIconIndex(keyToIconIndex)
            {
                Eegeo_ASSERT(!defaultKey.empty(), "defaultKey must not be empty");
                Eegeo_ASSERT((m_keyToIconIndex.find(defaultKey) != m_keyToIconIndex.end()), "keyToIconIndex must provide mapping for default key");
            }
            
            WorldPinIconMapping::~WorldPinIconMapping()
            {
                Eegeo_DELETE m_pTextureAtlas;
                Eegeo_GL(glDeleteTextures(1, &m_texturePage.textureId));
            }

            const Eegeo::Rendering::AtlasTexturePageLayout& WorldPinIconMapping::GetTexturePageLayout() const
            {
                return *m_pTextureAtlas;
            }

            const Eegeo::Helpers::GLHelpers::TextureInfo& WorldPinIconMapping::GetTextureInfo() const
            {
                return m_texturePage;
            }

            int WorldPinIconMapping::IconIndexForKey(const std::string& key) const
            {
                std::map<std::string, int>::const_iterator iter = m_keyToIconIndex.find(key);
                
                if (iter != m_keyToIconIndex.end())
                {
                    return iter->second;
                }
                else
                {
                    return m_keyToIconIndex.at(m_defaultKey);
                }
            }
        }
    }
}