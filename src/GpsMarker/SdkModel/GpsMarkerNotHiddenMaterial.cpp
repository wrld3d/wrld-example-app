// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "GpsMarkerNotHiddenMaterial.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "WorldMeshRenderable.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerNotHiddenMaterial::GpsMarkerNotHiddenMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                                   const std::string& name,
                                                                   GpsMarkerShader& shader,
                                                                   Eegeo::Rendering::TTextureId textureDayId,
                                                                   Eegeo::Rendering::TTextureId textureNightId,
                                                                   const Eegeo::v4& initialColor)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_textureDayId(textureDayId)
            , m_textureNightId(textureNightId)
            , m_textureLerpValue(0)
            , m_color(initialColor)
            , m_colorLerpValue(0)
            {
            }
            
            void GpsMarkerNotHiddenMaterial::SetState(Eegeo::Rendering::GLState &glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_GREATER);
                glState.DepthMask(GL_FALSE);
                
                glState.StencilTest.Enable();
                glState.StencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                glState.StencilFunc(GL_NOTEQUAL, Eegeo::Rendering::StencilMapLayerMask::Buildings, 0xffffffff);
                glState.StencilMask(0xffffffff);
                
                bool repeatTexture = false;
                Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_Linear;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseDaySamplerId(), m_textureDayId, textureMinifyType, repeatTexture);
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseNightSamplerId(), m_textureNightId, textureMinifyType, repeatTexture);
            }
            
            void GpsMarkerNotHiddenMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase *renderableBase, Eegeo::Rendering::GLState &glState) const
            {
                Eegeo::Rendering::Renderables::WorldMeshRenderable* pRenderable = (Eegeo::Rendering::Renderables::WorldMeshRenderable*) renderableBase;
                m_shader.SetMVP(pRenderable->GetModelViewProjection());
                m_shader.SetTextureLerpValue(m_textureLerpValue);
                m_shader.SetColor(m_color);
                m_shader.SetColorLerpValue(m_colorLerpValue);
            }
        }
    }
}