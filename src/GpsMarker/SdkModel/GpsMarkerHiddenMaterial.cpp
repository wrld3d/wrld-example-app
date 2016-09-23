// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "GpsMarkerHiddenMaterial.h"
#include "WorldMeshRenderable.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerHiddenMaterial::GpsMarkerHiddenMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                             const std::string& name,
                                                             Eegeo::Rendering::Shaders::ColorShader& shader,
                                                             const Eegeo::v4& initialColor)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_color(initialColor)
            {
            }
            
            void GpsMarkerHiddenMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_GREATER);
                glState.DepthMask(GL_FALSE);
                
                glState.StencilTest.Enable();
                glState.StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                glState.StencilFunc(GL_EQUAL, Eegeo::Rendering::StencilMapLayerMask::Buildings, 0xffffffff);
                glState.StencilMask(0xffffffff);
            }
            
            void GpsMarkerHiddenMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase *renderableBase, Eegeo::Rendering::GLState &glState) const
            {
                Eegeo::Rendering::Renderables::WorldMeshRenderable* pRenderable = (Eegeo::Rendering::Renderables::WorldMeshRenderable*) renderableBase;
                m_shader.SetMVP(pRenderable->GetModelViewProjection());
                m_shader.SetColor(m_color);
            }
        }
    }
}