// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LocalTextureFactory.h"

#include "GLHelpers.h"
#include "ITextureFileLoader.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            LocalTextureFactory::LocalTextureFactory(Eegeo::Helpers::ITextureFileLoader& textureFileLoader)
            : m_textureFileLoader(textureFileLoader)
            {
            }
            
            LocalTextureFactory::~LocalTextureFactory()
            {
                for(std::map<std::string,LocalTexture*>::iterator it = m_loadedTextures.begin(); it != m_loadedTextures.end(); ++it)
                {
                    Eegeo_DELETE it->second;
                }
            }
            
            LocalTexture& LocalTextureFactory::CreateTexture(std::string filename)
            {
                if(m_loadedTextures.find(filename) == m_loadedTextures.end())
                {
                    Eegeo::Helpers::GLHelpers::TextureInfo textureInfo;
                    const bool generateMipmaps = true;
                    bool success = m_textureFileLoader.LoadTexture(textureInfo, filename, generateMipmaps);
                    Eegeo_ASSERT(success, "failed to load texture");
                    
                    m_loadedTextures[filename] = Eegeo_NEW(LocalTexture)(filename, textureInfo);
                }
                return *m_loadedTextures[filename];
            }
        }
    }
}