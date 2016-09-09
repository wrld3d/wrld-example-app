// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "VectorMath.h"
#include "Camera.h"
#include "IRenderableFilter.h"
#include "Rendering.h"
#include "RenderingModule.h"
#include "ITextureFileLoader.h"
#include "IFileIO.h"
#include "IAsyncTextureRequestor.h"
#include "GLHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingView : private Eegeo::NonCopyable, public Eegeo::Rendering::IRenderableFilter
                {
                public:
                    PoiRingView(const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                                const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                                const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                                const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool,
                                const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                                const std::shared_ptr<Eegeo::Helpers::ITextureFileLoader>& textureFileLoader,
                                const std::shared_ptr<PoiRingRenderable>& poiRingRenderable);

                    ~PoiRingView();

                    void SetRingTransforms(const Eegeo::m44& sphereMvp) const;
                    void SetInnerSphereScale(const float scale);

                    void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                    void SetShouldRenderRing(bool shouldRenderRing);

                    void AddIconSprite(const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& position, float scale);

                private:
                    const std::shared_ptr<PoiRingRenderable> m_poiRingRenderable;
                    std::shared_ptr<Eegeo::Rendering::Shaders::BatchedSpriteShader> m_shader;
                    std::shared_ptr<Eegeo::Rendering::Materials::BatchedSpriteMaterial> m_material;
                    std::shared_ptr<Eegeo::Rendering::Renderables::BatchedSpriteRenderable> m_iconRenderable;
                    
                    Eegeo::Helpers::GLHelpers::TextureInfo m_poiRingIconTexture;

                    bool m_shouldRenderRing;
                };
            }
        }
    }
}
