// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "TexturedUniformColoredShader.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerMaterial : protected Eegeo::NonCopyable, public Eegeo::Rendering::Materials::IMaterial
            {
            public:
                GpsMarkerMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                  const std::string& name,
                                  Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                  Eegeo::Rendering::TTextureId textureId,
                                  const Eegeo::v4& initialColor);
                
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const { return m_shader; }
                const std::string& GetName() const { return m_name; }
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                
                void SetColor(Eegeo::v4& color) { m_color = color; }
                const Eegeo::v4& GetColor() const { return m_color; }
                
            protected:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_name;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader& m_shader;
                Eegeo::Rendering::TTextureId m_textureId;
                Eegeo::v4 m_color;
            };
        }
    }
}