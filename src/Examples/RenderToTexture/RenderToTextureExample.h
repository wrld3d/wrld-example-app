// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RenderToTextureExample__
#define __ExampleApp__RenderToTextureExample__

#include "IExample.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "RenderToTextureExampleIncludes.h"

namespace Examples
{
    class RenderToTextureExample : public IExample
    {
    private:
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        Eegeo::Rendering::RenderContext& m_renderContext;
        Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
        Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
        Eegeo::Rendering::Shaders::ShaderIdGenerator& m_shaderIdGenerator;
        Eegeo::Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
        Eegeo::Rendering::RenderableFilters& m_renderableFilters;
        Eegeo::Rendering::GlBufferPool& m_glBufferPool;
        
        PostProcessVignetteShader* m_pVignetteShader;
        PostProcessVignetteMaterial* m_pVignetteMaterial;
        Eegeo::Rendering::VertexLayouts::VertexLayout* m_pMeshVertexLayout;
        //TexturedClipSpaceMeshFactory* m_pMeshFactory;
        Eegeo::Rendering::Mesh* m_pRenderableMesh;
        PostProcessVignetteRenderable* m_pRenderable;
        PostProcessVignetteRenderer* m_pVignetteRenderer;
        Eegeo::Rendering::RenderTexture* m_pRenderTexture;
        
        static const float SecondsBetweenEffectUpdates;
        float m_secondsSinceLastEffectUpate;
        
        void UpdateEffect();
        
    public:
        RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                               Eegeo::Rendering::RenderContext& renderContext,
                               Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                               Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                               Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                               Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                               Eegeo::Rendering::RenderableFilters& renderableFilters,
                               Eegeo::Rendering::GlBufferPool& m_glBufferPool);
        
        static std::string GetName()
        {
            return "RenderToTextureExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt);
        void PreWorldDraw();
        void Draw() {}
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__RenderToTextureExample__) */
