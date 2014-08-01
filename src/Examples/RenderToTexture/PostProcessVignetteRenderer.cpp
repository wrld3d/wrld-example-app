// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RenderContext.h"
#include "RenderQueue.h"
#include "PostProcessVignetteRenderable.h"
#include "PostProcessVignetteRenderer.h"

namespace Examples
{
    PostProcessVignetteRenderer::PostProcessVignetteRenderer(PostProcessVignetteRenderable& renderable)
    : m_renderable(renderable)
    {
        
    }
    
    void PostProcessVignetteRenderer::EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext,
                                                         Eegeo::Rendering::RenderQueue& renderQueue)
    {
        renderQueue.EnqueueRenderable(m_renderable);
    }
}
