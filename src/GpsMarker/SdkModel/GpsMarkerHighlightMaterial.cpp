// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "GpsMarkerHighlightMaterial.h"
#include "WorldMeshRenderable.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerHighlightMaterial::GpsMarkerHighlightMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                                   const std::string& name,
                                                                   Eegeo::Rendering::Shaders::ColorShader& shader,
                                                                   const Eegeo::v4& initialColor)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_color(initialColor)
            {
            }
            
            void GpsMarkerHighlightMaterial::SetState(Eegeo::Rendering::GLState &glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthMask(GL_FALSE);
                glState.DepthTest.Disable();
                glState.CullFaceMode(GL_BACK);
            }
            
            void GpsMarkerHighlightMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase *renderableBase, Eegeo::Rendering::GLState &glState) const
            {
                Eegeo::Rendering::Renderables::WorldMeshRenderable* pRenderable = (Eegeo::Rendering::Renderables::WorldMeshRenderable*) renderableBase;
                m_shader.SetMVP(pRenderable->GetModelViewProjection());
                m_shader.SetColor(m_color);
            }
        }
    }
}