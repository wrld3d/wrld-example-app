// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UnlitTexturedMaterialFactory.h"

#include "Colors.h"
#include "MaterialIdGenerator.h"
#include "ShaderIdGenerator.h"
#include "TexturedUniformColoredShader.h"
#include "UnlitTexturedMaterial.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            UnlitTexturedMaterialFactory::UnlitTexturedMaterialFactory(Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                                                                         Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator)
            : m_materialIdGenerator(materialIdGenerator)
            , m_pShader(NULL)
            {
                m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(shaderIdGenerator.GetNextId());
            }
            
            UnlitTexturedMaterialFactory::~UnlitTexturedMaterialFactory()
            {
                Eegeo_DELETE m_pShader;
            }
            
            Eegeo::Rendering::Materials::IMaterial* UnlitTexturedMaterialFactory::CreateMaterial(Eegeo::Rendering::TTextureId textureId, std::string materialName)
            {
                return Eegeo_NEW(UnlitTexturedMaterial)(m_materialIdGenerator.GetNextId(),
                                                        materialName,
                                                        *m_pShader,
                                                        textureId);
            }
        }
    }
}
