// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "Types.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class UnlitTexturedMaterial : public Eegeo::Rendering::Materials::IMaterial, Eegeo::NonCopyable
            {
            public:
                UnlitTexturedMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                      const std::string& debugName,
                                      Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                      Eegeo::Rendering::TTextureId textureId);
                
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const;
                const std::string& GetName() const { return m_debugName; }
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                
            protected:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_debugName;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader& m_shader;
                Eegeo::Rendering::TTextureId m_textureId;
            };
        }
    }
}