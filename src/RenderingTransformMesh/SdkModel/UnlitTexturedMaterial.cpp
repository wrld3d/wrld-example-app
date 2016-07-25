// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UnlitTexturedMaterial.h"

#include "TexturedUniformColoredShader.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "RenderableBase.h"
#include "Colors.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            
            UnlitTexturedMaterial::UnlitTexturedMaterial(
                                                                               const Eegeo::Rendering::TMaterialId materialId,
                                                                               const std::string& debugName,
                                                                               Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                                                               Eegeo::Rendering::TTextureId textureId)
            : m_id(materialId)
            , m_debugName(debugName)
            , m_shader(shader)
            , m_textureId(textureId)
            {
                
            }
            
            const Eegeo::Rendering::Shader& UnlitTexturedMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void UnlitTexturedMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_LEQUAL);
                glState.CullFace.Enable();
                glState.FrontFace(GL_CW);
                glState.CullFaceMode(GL_BACK);
                glState.StencilTest.Disable();
                
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.ColorMask(true, true, true, true);
                
                glState.Blend.Enable();
                glState.DepthMask(GL_FALSE);
                
                bool repeatTexture = false;
                Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_LinearMipmap_Linear;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseSamplerId(), m_textureId, textureMinifyType, repeatTexture);
            }
            
            void UnlitTexturedMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                m_shader.SetMVP(renderableBase->GetModelViewProjection());
                m_shader.SetColor(Eegeo::Rendering::Colors::WHITE);
            }
        }
    }
}