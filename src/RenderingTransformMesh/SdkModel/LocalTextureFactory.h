// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "Helpers.h"
#include "Types.h"
#include "LocalTexture.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class LocalTextureFactory : Eegeo::NonCopyable
            {
            private:
                Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
                std::map<std::string,LocalTexture*> m_loadedTextures;
                
            public:
                LocalTextureFactory(Eegeo::Helpers::ITextureFileLoader& textureFileLoader);
                
                ~LocalTextureFactory();
                
                LocalTexture& CreateTexture(std::string filename);
                
            };
        }
    }
}