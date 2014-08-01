// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PostProcessVignetteMaterial__
#define __ExampleApp__PostProcessVignetteMaterial__

#include <string>
#include "Types.h"
#include "IMaterial.h"
#include "Rendering.h"
#include "RenderToTextureExampleIncludes.h"
#include "RenderTexture.h"

namespace Examples
{
    class PostProcessVignetteMaterial : Eegeo::NonCopyable, public Eegeo::Rendering::Materials::IMaterial
    {
    public:
        PostProcessVignetteMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                    const std::string& name,
                                    PostProcessVignetteShader& shader,
                                    Eegeo::Rendering::RenderTexture& renderTexture);
        
        const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
        const Eegeo::Rendering::Shader& GetShader() const;
        const std::string& GetName() const { return m_name; }
        
        void SetState(Eegeo::Rendering::GLState& glState) const;
        
        void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase,
                                   Eegeo::Rendering::GLState& glState) const;
        
    private:
        const Eegeo::Rendering::TMaterialId m_id;
        const std::string m_name;
        PostProcessVignetteShader& m_shader;
        Eegeo::Rendering::RenderTexture& m_renderTexture;
    };
}

#endif /* defined(__ExampleApp__PostProcessVignetteMaterial__) */
