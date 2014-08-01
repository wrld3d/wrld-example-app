// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include "RenderTexture.h"
#include "RenderContext.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "RenderableFilters.h"
#include "GlBufferPool.h"
#include "VertexBindingPool.h"
#include "Mesh.h"
#include "VertexLayout.h"
#include "PostProcessVignetteShader.h"
#include "PostProcessVignetteMaterial.h"
#include "PostProcessVignetteRenderer.h"
#include "PostProcessVignetteRenderable.h"
#include "TexturedClipSpaceVertexLayout.h"
#include "TexturedClipSpaceVertex.h"
#include "TexturedClipSpaceMeshFactory.h"
#include "RenderToTextureExample.h"

namespace
{
    void InitialiseMeshBuffers(std::vector<Examples::TexturedClipSpaceVertex>& vertexBuffer,
                               std::vector<u16>& indexBuffer);
}

namespace Examples
{
    //Give the effect a 10 frames per second intensity update to give it an old-timey movie vibe...
    const float RenderToTextureExample::SecondsBetweenEffectUpdates = 0.1f;
    
    RenderToTextureExample::RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                                                   Eegeo::Rendering::RenderContext& renderContext,
                                                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                   Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                                   Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                                   Eegeo::Rendering::RenderableFilters& renderableFilters,
                                                   Eegeo::Rendering::GlBufferPool& glBufferPool)
    :m_globeCameraStateRestorer(cameraController)
    ,m_renderContext(renderContext)
    ,m_vertexBindingPool(vertexBindingPool)
    ,m_shaderIdGenerator(shaderIdGenerator)
    ,m_materialIdGenerator(materialIdGenerator)
    ,m_renderableFilters(renderableFilters)
    ,m_glBufferPool(glBufferPool)
    ,m_pVignetteShader(NULL)
    ,m_pVignetteMaterial(NULL)
    ,m_pMeshVertexLayout(NULL)
    ,m_pMeshFactory(NULL)
    ,m_pRenderableMesh(NULL)
    ,m_pRenderable(NULL)
    ,m_pVignetteRenderer(NULL)
    ,m_secondsSinceLastEffectUpate(0.f)
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

        m_pVignetteShader = PostProcessVignetteShader::Create(m_shaderIdGenerator.GetNextId());
        
        m_pVignetteMaterial = Eegeo_NEW(PostProcessVignetteMaterial)(m_materialIdGenerator.GetNextId(),
                                                                     "PostProcessVignetteMaterial",
                                                                     *m_pVignetteShader,
                                                                     *m_pRenderTexture);
        
        m_pMeshVertexLayout = CreateTexturedClipSpaceLayout();
        
        m_pMeshFactory = Eegeo_NEW(TexturedClipSpaceMeshFactory)(m_glBufferPool, *m_pMeshVertexLayout, sizeof(TexturedClipSpaceVertex));
        
        std::vector<TexturedClipSpaceVertex> renderVertices;
        std::vector<u16> renderIndices;
        
        InitialiseMeshBuffers(renderVertices, renderIndices);
        
        m_pRenderableMesh = m_pMeshFactory->CreateMesh(renderVertices.data(),
                                                       renderVertices.size(),
                                                       renderIndices.data(),
                                                       (sizeof(u16) * renderIndices.size()),
                                                       renderIndices.size(),
                                                       "PostProcessVignetteTexturedClipSpaceMesh");
        
        const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = m_pRenderableMesh->GetVertexLayout();
        const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_pVignetteShader->GetVertexAttributes();
        const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);
        
        m_pRenderable = Eegeo_NEW(PostProcessVignetteRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                                                 m_pVignetteMaterial,
                                                                 vertexBinding,
                                                                 m_pRenderableMesh);
        
        m_pVignetteRenderer = Eegeo_NEW(PostProcessVignetteRenderer)(*m_pRenderable);
        
        m_renderableFilters.AddRenderableFilter(m_pVignetteRenderer);
        
        UpdateEffect();
    }
    
    void RenderToTextureExample::Suspend()
    {
        m_renderableFilters.RemoveRenderableFilter(m_pVignetteRenderer);
        
        Eegeo_DELETE m_pVignetteRenderer;
        m_pVignetteRenderer = NULL;
        
        Eegeo_DELETE m_pRenderable;
        m_pRenderable = NULL;
        
        Eegeo_DELETE m_pMeshFactory;
        m_pMeshFactory = NULL;
        
        Eegeo_DELETE m_pMeshVertexLayout;
        m_pMeshVertexLayout = NULL;
        
        Eegeo_DELETE m_pVignetteMaterial;
        m_pVignetteMaterial = NULL;
        
        Eegeo_DELETE m_pVignetteShader;
        m_pVignetteShader = NULL;
        
        Eegeo_DELETE m_pRenderTexture;
        m_pRenderTexture = NULL;
    }
    
    void RenderToTextureExample::PreWorldDraw()
    {
        // Before the world is rendered, we should switch to rendering into our texture...
        m_pRenderTexture->BeginRendering();
    }
    
    void RenderToTextureExample::Update(float dt)
    {
        m_secondsSinceLastEffectUpate += dt;
        if (m_secondsSinceLastEffectUpate > SecondsBetweenEffectUpdates)
        {
            UpdateEffect();
            m_secondsSinceLastEffectUpate = 0.f;
        }
    }
    
    void RenderToTextureExample::UpdateEffect()
    {
        // Set the vignette effect data for this frame (the colour and a radial intensity change)...
        m_pRenderable->SetVignetteColour(Eegeo::v3(0.9f, 0.8f, 0.6f));
        const float radiusIntensityVariance = (2-(rand()%5))/10.f;
        m_pRenderable->SetVignetteRadiusModifier(3.6f + radiusIntensityVariance);
    }
}

namespace
{
    void InitialiseMeshBuffers(std::vector<Examples::TexturedClipSpaceVertex>& vertexBuffer,
                               std::vector<u16>& indexBuffer)
    {
        vertexBuffer.resize(4);
        
        vertexBuffer[0].m_x = -1.f;
        vertexBuffer[0].m_y = 1.f;
        vertexBuffer[0].m_u = 0.f;
        vertexBuffer[0].m_v = 1.f;
        
        vertexBuffer[1].m_x = 1.f;
        vertexBuffer[1].m_y = 1.f;
        vertexBuffer[1].m_u = 1.f;
        vertexBuffer[1].m_v = 1.f;
        
        vertexBuffer[2].m_x = -1.f;
        vertexBuffer[2].m_y = -1.f;
        vertexBuffer[2].m_u = 0.f;
        vertexBuffer[2].m_v = 0.f;
        
        vertexBuffer[3].m_x = 1.f;
        vertexBuffer[3].m_y = -1.f;
        vertexBuffer[3].m_u = 1.f;
        vertexBuffer[3].m_v = 0.f;
        
        indexBuffer.resize(6);
        
        indexBuffer[0] = 0;
        indexBuffer[1] = 1;
        indexBuffer[2] = 2;
        
        indexBuffer[3] = 1;
        indexBuffer[4] = 3;
        indexBuffer[5] = 2;
    }
}

