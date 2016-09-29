// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "GpsMarkerShader.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerNotHiddenMaterial : protected Eegeo::NonCopyable, public Eegeo::Rendering::Materials::IMaterial
            {
            public:
                GpsMarkerNotHiddenMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                           const std::string& name,
                                           GpsMarkerShader& shader,
                                           Eegeo::Rendering::TTextureId textureDayId,
                                           Eegeo::Rendering::TTextureId textureNightId,
                                           const Eegeo::v4& initialColor);
                
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const { return m_shader; }
                const std::string& GetName() const { return m_name; }
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                
                void SetTextureLerpValue(float textureLerpValue) { m_textureLerpValue = textureLerpValue; }
                float GetTextureLerpValue() const { return m_textureLerpValue; }
                
                void SetColor(Eegeo::v4& color) { m_color = color; }
                const Eegeo::v4& GetColor() const { return m_color; }
                
                void SetColorLerpValue(float colorLerpValue) { m_colorLerpValue = colorLerpValue; }
                float GetColorLerpValue() const { return m_colorLerpValue; }
                
            protected:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_name;
                GpsMarkerShader& m_shader;
                Eegeo::Rendering::TTextureId m_textureDayId;
                Eegeo::Rendering::TTextureId m_textureNightId;
                float m_textureLerpValue;
                Eegeo::v4 m_color;
                float m_colorLerpValue;
            };
        }
    }
}