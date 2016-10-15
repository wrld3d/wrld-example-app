// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Shader.h"
#include "IdTypes.h"
#include "Graphics.h"
#include "VectorMath.h"
#include "Rendering.h"
#include <string>

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            namespace GpsMarkerShaderCode
            {
                const std::string PositionName = "Position";
                const std::string UVName = "UV";
                const std::string ModelViewProjectionMatrixName = "ModelViewProjectionMatrix";
                
                const std::string _vertexDecls =
                        "attribute highp vec3 "+PositionName+";\n"
                        "attribute mediump vec2 "+UVName+";\n"
                        "varying mediump vec2 DestinationUV;\n"
                        "uniform highp mat4 "+ModelViewProjectionMatrixName+";\n";
                
                const std::string DiffuseDayName = "DiffuseDay";
                const std::string DiffuseNightName = "DiffuseNight";
                const std::string TextureLerpValueName = "TextureLerpValue";
                const std::string ColorName = "ColorName";
                const std::string ColorLerpValueName = "ColorLerpValue";
                
                const std::string _fragmentDecls =
                        "varying mediump vec2 DestinationUV;\n"
                        "uniform sampler2D "+DiffuseDayName+";\n"
                        "uniform sampler2D "+DiffuseNightName+";\n"
                        "uniform lowp float "+TextureLerpValueName+";\n"
                        "uniform lowp vec4 "+ColorName+";\n"
                        "uniform lowp float "+ColorLerpValueName+";\n";
                
                const std::string _vertexCode = "void main(void) { \n"
                        "DestinationUV = UV;\n"
                        "gl_Position = ModelViewProjectionMatrix * vec4(Position.xyz, 1.0);\n"
                        "}";
                
                const std::string _fragmentCode = "void main(void) { \n"
                        "highp vec4 textureColor = mix(texture2D("+DiffuseDayName+", DestinationUV.xy), texture2D("+DiffuseNightName+", DestinationUV.xy), "+TextureLerpValueName+");\n"
                        "gl_FragColor = mix(textureColor, "+ColorName+", "+ColorLerpValueName+");\n"
                        "}";
            }
            
            class GpsMarkerShader : public Eegeo::Rendering::Shader
            {
            public:
                static GpsMarkerShader* Create(const Eegeo::Rendering::TShaderId shaderId)
                {
                    return Eegeo_NEW(GpsMarkerShader)(shaderId,
                                                      GpsMarkerShaderCode::_vertexDecls + GpsMarkerShaderCode::_vertexCode,
                                                      GpsMarkerShaderCode::_fragmentDecls + GpsMarkerShaderCode::_fragmentCode);
                }
                
                const GLuint GetDiffuseDaySamplerId() const { return 0; }
                const GLuint GetDiffuseNightSamplerId() const { return 1; }
                
                void SetMVP(const Eegeo::m44& mvp) const
                {
                    bool transpose = false;
                    SetUniformM44(mvp, m_mvpUniformLocation, transpose);
                }
                
                void SetColor(const Eegeo::v4& color) const
                {
                    SetUniformV4(color, m_colorUniformLocation);
                }
                
                void SetColorLerpValue(float colorLerpValue) const
                {
                    SetUniformFloat(colorLerpValue, m_colorLerpValueLocation);
                }
                
                void SetTextureLerpValue(float textureLerpValue) const
                {
                    SetUniformFloat(textureLerpValue, m_textureLerpValueLocation);
                }
                
                void Use(Eegeo::Rendering::GLState& glState) const
                {
                    UseProgram(glState);
                    SetUniformTextureSampler(glState, GetDiffuseDaySamplerId(), m_diffuseDayTextureSamplerUniformLocation);
                    SetUniformTextureSampler(glState, GetDiffuseNightSamplerId(), m_diffuseNightTextureSamplerUniformLocation);
                }
                
            protected:
                GpsMarkerShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode) : Shader(shaderId)
                {
                    CompileProgram(vertexShaderCode, fragmentShaderCode);
                    
                    m_mvpUniformLocation = GetUniformLocation(GpsMarkerShaderCode::ModelViewProjectionMatrixName);
                    m_colorUniformLocation = GetUniformLocation(GpsMarkerShaderCode::ColorName);
                    m_diffuseDayTextureSamplerUniformLocation = GetUniformLocation(GpsMarkerShaderCode::DiffuseDayName);
                    m_diffuseNightTextureSamplerUniformLocation = GetUniformLocation(GpsMarkerShaderCode::DiffuseNightName);
                    m_colorLerpValueLocation = GetUniformLocation(GpsMarkerShaderCode::ColorLerpValueName);
                    m_textureLerpValueLocation = GetUniformLocation(GpsMarkerShaderCode::TextureLerpValueName);
                }
                
            private:
                GLuint m_mvpUniformLocation;
                GLuint m_colorUniformLocation;
                GLfloat m_colorLerpValueLocation;
                GLuint m_diffuseDayTextureSamplerUniformLocation;
                GLuint m_diffuseNightTextureSamplerUniformLocation;
                GLfloat m_textureLerpValueLocation;
            };
        }
    }
}