// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"
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
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerViewFactory : private Eegeo::NonCopyable
            {
            public:
                
                GpsMarkerViewFactory(const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                                     const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                                     const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                                     const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool,
                                     const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                                     const std::shared_ptr<Eegeo::Helpers::ITextureFileLoader>& textureFileLoader);
                ~GpsMarkerViewFactory();
                
                Eegeo::Rendering::Renderables::BatchedSpriteRenderable& GetRenderable() const;
            private:
                Eegeo::Helpers::GLHelpers::TextureInfo m_gpsIconTexture;
                std::shared_ptr<Eegeo::Rendering::Renderables::BatchedSpriteRenderable> m_iconRenderable;
                std::shared_ptr<Eegeo::Rendering::Materials::BatchedSpriteMaterial> m_material;
                std::shared_ptr<Eegeo::Rendering::Shaders::BatchedSpriteShader> m_shader;
            };
        }
    }
}