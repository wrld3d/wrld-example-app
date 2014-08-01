// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PostProcessVignetteShader__
#define __ExampleApp__PostProcessVignetteShader__

#include "Shader.h"
#include "Rendering.h"
#include "Graphics.h"

namespace Examples
{
    class PostProcessVignetteShader : public Eegeo::Rendering::Shader
    {
    public:
        static PostProcessVignetteShader* Create(const Eegeo::Rendering::TShaderId shaderId);
        
        void Use(Eegeo::Rendering::GLState& glState) const;
        
        void SetVignetteColour(const Eegeo::v3& vignetteColour);
        
        void SetVignetteRadiusModifier(float vignetteRadiusModifier);
        
        virtual void SetMVP(const Eegeo::m44& mvp) const;
        
        GLuint GetDiffuseSamplerId() const;
        
    private:
        PostProcessVignetteShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode);
        
        GLuint m_diffuseTextureSamplerUniformLocation;
        GLuint m_vignetteColourUniform;
        GLuint m_vignetteRadiusModifierUniform;
    };
}

#endif /* defined(__ExampleApp__PostProcessVignetteShader__) */
