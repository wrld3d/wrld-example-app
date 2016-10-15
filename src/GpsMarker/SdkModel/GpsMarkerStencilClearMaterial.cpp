// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "GpsMarkerStencilClearMaterial.h"
#include "WorldMeshRenderable.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerStencilClearMaterial::GpsMarkerStencilClearMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                                         const std::string& name,
                                                                         Eegeo::Rendering::Shaders::ColorShader& shader,
                                                                         const Eegeo::v4& initialColor)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_color(initialColor)
            {
            }
            
            void GpsMarkerStencilClearMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                
                glState.DepthTest.Disable();
                glState.DepthMask(GL_FALSE);
                
                glState.StencilTest.Enable();
                glState.StencilOpSeparate(GL_FRONT_AND_BACK, GL_ZERO, GL_ZERO, GL_ZERO);
                glState.StencilFunc(GL_ALWAYS, 0, 0);
                glState.StencilMask(0xffffffff);
            }
            
            void GpsMarkerStencilClearMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase *renderableBase, Eegeo::Rendering::GLState &glState) const
            {
                Eegeo::Rendering::Renderables::WorldMeshRenderable* pRenderable = (Eegeo::Rendering::Renderables::WorldMeshRenderable*) renderableBase;
                m_shader.SetMVP(pRenderable->GetModelViewProjection());
                m_shader.SetColor(m_color);
            }
        }
    }
}