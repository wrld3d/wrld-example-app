// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RenderToTextureExample__
#define __ExampleApp__RenderToTextureExample__

#include "IExample.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "PostProcessVignetteRenderer.h"

namespace Examples
{
    class RenderToTextureExample : public IExample
    {
    private:
        PostProcessVignetteRenderer m_renderer;
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        Eegeo::Rendering::RenderTexture* m_pRenderTexture;
        Eegeo::Rendering::RenderContext& m_renderContext;
        
    public:
        RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                               Eegeo::Rendering::RenderContext& renderContext);
        
        static std::string GetName()
        {
            return "RenderToTextureExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt) {}
        void PreWorldDraw();
        void Draw();
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__RenderToTextureExample__) */
