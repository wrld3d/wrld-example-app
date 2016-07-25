// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "GLHelpers.h"
#include "Types.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class LocalTexture : Eegeo::NonCopyable
            {
            private:
                std::string m_name;
                Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
                
            public:
                //This class will take ownership of the gl texture referenced by the TextureInfo and release it on delete
                LocalTexture(const std::string& name, const Eegeo::Helpers::GLHelpers::TextureInfo& textureInfo);
                
                ~LocalTexture();
                
                const Eegeo::Helpers::GLHelpers::TextureInfo& GetTextureInfo() const;
                
                const std::string& GetName() const;
            };
        }
    }
}