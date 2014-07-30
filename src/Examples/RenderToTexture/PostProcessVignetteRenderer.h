// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PostProcessVignetteRenderer__
#define __ExampleApp__PostProcessVignetteRenderer__

#include <string>
#include "Types.h"
#include "Rendering.h"

namespace Examples
{
    // This class applies a simple effect to the texture supplied to its Draw() method, and renders to a full-screen quad.
    class PostProcessVignetteRenderer
    {
        struct PostProcessVignetteShader
        {
            int m_positionSlot;
            int m_uvSlot;
            int m_samplerSlot;
            u32 m_programHandle;
        };
        
        struct PostProcessVignetteVertex
        {
            float m_x, m_y;
            float m_u, m_v;
        };
        
        PostProcessVignetteShader m_shader;
        u32 m_glVertexBuffer;
        u32 m_glIndexBuffer;
        Eegeo::Rendering::RenderContext& m_renderContext;
        
        std::string VertexShader();
        std::string FragmentShader();
        void CompileShaders();
        void BuildGeometry();
        
    public:
        PostProcessVignetteRenderer(Eegeo::Rendering::RenderContext& renderContext);
        ~PostProcessVignetteRenderer();
        
        void Draw(unsigned textureId);
    };
}

#endif /* defined(__ExampleApp__PostProcessVignetteRenderer__) */
