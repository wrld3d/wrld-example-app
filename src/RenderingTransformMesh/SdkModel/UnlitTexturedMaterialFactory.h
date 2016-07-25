// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "IdTypes.h"
#include "Rendering.h"
#include "Types.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class UnlitTexturedMaterialFactory : Eegeo::NonCopyable
            {
            private:
                Eegeo::Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pShader;
                
            public:
                UnlitTexturedMaterialFactory(Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator, Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator);
                
                ~UnlitTexturedMaterialFactory();
                
                Eegeo::Rendering::Materials::IMaterial* CreateMaterial(Eegeo::Rendering::TTextureId textureId, std::string materialName);
            };
        }
    }
}