// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PostProcessVignetteRenderer__
#define __ExampleApp__PostProcessVignetteRenderer__

#include "Types.h"
#include "IRenderableFilter.h"
#include "Rendering.h"
#include "RenderToTextureExampleIncludes.h"

namespace Examples
{
    class PostProcessVignetteRenderer : Eegeo::NonCopyable, public Eegeo::Rendering::IRenderableFilter
    {
    public:
        PostProcessVignetteRenderer(PostProcessVignetteRenderable& renderable);
        
        void EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
    private:
        PostProcessVignetteRenderable& m_renderable;
    };
}

#endif /* defined(__ExampleApp__PostProcessVignetteRenderer__) */
