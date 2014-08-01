// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PostProcessVignetteMaterial.h"
#include "Rendering.h"
#include "VectorMath.h"
#include "PostProcessVignetteShader.h"
#include "PostProcessVignetteRenderable.h"

namespace Examples
{
    PostProcessVignetteMaterial::PostProcessVignetteMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                             const std::string& name,
                                                             PostProcessVignetteShader& shader,
                                                             Eegeo::Rendering::RenderTexture& renderTexture)
    : m_id(materialId)
    , m_name(name)
    , m_shader(shader)
    , m_renderTexture(renderTexture)
    {
        
    }
    
    const Eegeo::Rendering::Shader& PostProcessVignetteMaterial::GetShader() const
    {
        return m_shader;
    }
    
    void PostProcessVignetteMaterial::SetState(Eegeo::Rendering::GLState& glState) const
    {
        m_shader.Use(glState);

        // Assume rendering into this texture this has been started elsewhere prior to drawing...
        m_renderTexture.EndRendering();
        
        const bool repeat = false;
        Eegeo::Helpers::GLHelpers::BindTexture2D(glState,
                                                 m_shader.GetDiffuseSamplerId(),
                                                 m_renderTexture.TextureId(),
                                                 Eegeo::Rendering::TextureMinify_Nearest,
                                                 repeat);
    }
    
    void PostProcessVignetteMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* pRenderableBase,
                                                            Eegeo::Rendering::GLState& glState) const
    {
        const PostProcessVignetteRenderable* renderable = static_cast<const PostProcessVignetteRenderable*>(pRenderableBase);
        
        m_shader.SetVignetteColour(renderable->GetVignetteColour());
        m_shader.SetVignetteRadiusModifier(renderable->GetVignetteRadiusModifier());
    }
}