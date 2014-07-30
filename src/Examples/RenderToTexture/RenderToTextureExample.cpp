// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include "RenderTexture.h"
#include "RenderContext.h"
#include "PostProcessVignetteRenderer.h"
#include "RenderToTextureExample.h"

using namespace Examples;


RenderToTextureExample::RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                                               Eegeo::Rendering::RenderContext& renderContext)
:m_globeCameraStateRestorer(cameraController)
,m_renderContext(renderContext)
,m_renderer(renderContext)
{
}

void RenderToTextureExample::Start()
{
    // Allocate a full screen sized texture to render into, with depth and stencil attachments.
    //
    // This example assumes that the hardware is capable of allocating a RenderBuffer with a colour,
    // depth and stencil attachment, which should always be the case for iOS. 
    //
    
    const bool needsDepthStencilBuffers = true;
    m_pRenderTexture = Eegeo_NEW(Eegeo::Rendering::RenderTexture)(m_renderContext.GetScreenWidth(),
                                                                  m_renderContext.GetScreenHeight(),
                                                                  needsDepthStencilBuffers);
}

void RenderToTextureExample::Suspend()
{
    // Release the texture to render into, and its associated buffers.
    Eegeo_DELETE m_pRenderTexture;
    m_pRenderTexture = NULL;
}

void RenderToTextureExample::PreWorldDraw()
{
    // Before the world is rendered, we should switch to rendering into our texture...
    m_pRenderTexture->BeginRendering();
}

void RenderToTextureExample::Draw()
{
    // This Draw() method is called after the rendering environment, so the environment is now rendered into our texture.
    // We now switch back to rendering to the main frame buffer.
    m_pRenderTexture->EndRendering();
    
    // Pass the texture name to our post processing renderer, which can apply an effect to the rendered scene.
    m_renderer.Draw(m_pRenderTexture->TextureId());
}




