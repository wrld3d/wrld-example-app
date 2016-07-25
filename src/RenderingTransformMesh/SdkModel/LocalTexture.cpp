// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LocalTexture.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            LocalTexture::LocalTexture(const std::string& name, const Eegeo::Helpers::GLHelpers::TextureInfo& textureInfo)
            : m_name(name)
            , m_textureInfo(textureInfo)
            {
            }
            
            LocalTexture::~LocalTexture()
            {
                if (m_textureInfo.textureId != 0)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
                }
            }
            
            const Eegeo::Helpers::GLHelpers::TextureInfo& LocalTexture::GetTextureInfo() const
            {
                return m_textureInfo;
            }
            
            const std::string& LocalTexture::GetName() const
            {
                return m_name;
            }
        }
    }
}