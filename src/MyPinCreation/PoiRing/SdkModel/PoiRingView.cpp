// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingView.h"
#include "RenderCamera.h"
#include "RenderQueue.h"
#include "PoiRingRenderable.h"
#include "RenderableFilters.h"
#include "BatchedSpriteRenderable.h"
#include "BatchedSpriteMaterial.h"
#include "MaterialIdGenerator.h"
#include "ShaderIdGenerator.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "GlBufferPool.h"
#include "Colors.h"
#include "Bounds.h"
#include "ITexturePageLayout.h"
#include "TextureNameHelpers.h"
#include "BatchedSpriteShader.h"
#include "ShaderIdGenerator.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingView::PoiRingView(const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                                         const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                                         const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                                         const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool,
                                         const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                                         const std::shared_ptr<Eegeo::Helpers::ITextureFileLoader>& textureFileLoader,
                                         const std::shared_ptr<PoiRingRenderable>& poiRingRenderable)
                    : m_poiRingRenderable(poiRingRenderable)
                    , m_shouldRenderRing(false)
                {
                    m_shader = std::shared_ptr<Eegeo::Rendering::Shaders::BatchedSpriteShader>(Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator->GetNextId()));
                    
                    textureFileLoader->LoadTexture(m_poiRingIconTexture,
                                                   Eegeo::Helpers::TextureNameHelpers::GetImageNameForDevice("poi_marker", ".png"),
                                                   false);
                    
                    m_material = std::shared_ptr<Eegeo::Rendering::Materials::BatchedSpriteMaterial>(Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator->GetNextId(),
                                                                                                           "Poi Creation Sprite Material",
                                                                                                           *m_shader,
                                                                                                           m_poiRingIconTexture.textureId,
                                                                                                           Eegeo::Rendering::TextureMinify_Nearest));
                    
                    const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = vertexBindingPool->GetVertexBinding(vertexLayoutPool->GetForTexturedColoredVertex(),
                                                                                                                                 m_shader->GetVertexAttributes());
                    
                    m_renderable = std::shared_ptr<Eegeo::Rendering::Renderables::BatchedSpriteRenderable>(Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                                                                                                                                                             m_material.get(),
                                                                                                                                                                             iconVertexBinding,
                                                                                                                                                                             *glBufferPool,
                                                                                                                                                                             Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Bottom));
                }

                PoiRingView::~PoiRingView()
                {
                }

                void PoiRingView::SetRingTransforms(const Eegeo::m44& sphereMvp) const
                {
                    m_poiRingRenderable->SetSphereMvp(sphereMvp);
                }

                void PoiRingView::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
                {
                    if (m_shouldRenderRing)
                    {
                        renderQueue.EnqueueRenderable(*m_poiRingRenderable);
                        renderQueue.EnqueueRenderable(*m_iconRenderable);
                    }
                }

                void PoiRingView::SetInnerSphereScale(const float scale)
                {
                    m_poiRingRenderable->SetInnerSphereScale(scale);
                }

                void PoiRingView::SetShouldRenderRing(bool shouldRenderRing)
                {
                    m_shouldRenderRing = shouldRenderRing;
                }

                void PoiRingView::AddIconSprite(const Eegeo::Camera::RenderCamera &renderCamera, const Eegeo::dv3& position, float scale)
                {
                    m_iconRenderable->Reset();
                    m_iconRenderable->SetModelViewProjection(renderCamera.GetViewProjectionMatrix());

                    const float dimensionInMeters = scale;

                    m_iconRenderable->AddSprite(renderCamera,
                                               position,
                                               Eegeo::v2(0, 0),
                                               Eegeo::v2(1, 1),
                                               Eegeo::Rendering::Colors::WHITE,
                                               Eegeo::v2(dimensionInMeters, dimensionInMeters));

                }
            }
        }
    }
}
