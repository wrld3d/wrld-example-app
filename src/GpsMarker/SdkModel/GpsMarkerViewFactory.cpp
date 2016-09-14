// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "GpsMarkerViewFactory.h"
#include "BatchedSpriteShader.h"
#include "BatchedSpriteMaterial.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "GlBufferPool.h"
#include "ITextureFileLoader.h"
#include "ImagePathHelpers.h"
#include "TextureNameHelpers.h"
#include "LayerIds.h"
#include "BatchedSpriteRenderable.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerViewFactory::GpsMarkerViewFactory(const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                                 const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                                 const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                                 const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool,
                                 const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                                 const std::shared_ptr<Eegeo::Helpers::ITextureFileLoader>& textureFileLoader)
            {
                m_shader = std::shared_ptr<Eegeo::Rendering::Shaders::BatchedSpriteShader>(Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator->GetNextId()));
                
                textureFileLoader->LoadTexture(m_gpsIconTexture,
                                               Eegeo::Helpers::TextureNameHelpers::GetImageNameForDevice("gps_marker", ".png"),
                                               false);
                                    
                m_material = std::shared_ptr<Eegeo::Rendering::Materials::BatchedSpriteMaterial>(Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator->GetNextId(),
                                                                                                                                                               "Gps icon Sprite Material",
                                                                                                                                                               *m_shader,
                                                                                                                                                               m_gpsIconTexture.textureId,
                                                                                                                                                               Eegeo::Rendering::TextureMinify_Nearest));
                
                const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = vertexBindingPool->GetVertexBinding(vertexLayoutPool->GetForTexturedColoredVertex(),
                                                                                                                              m_shader->GetVertexAttributes());
                
                m_iconRenderable = std::shared_ptr<Eegeo::Rendering::Renderables::BatchedSpriteRenderable>(Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                                                                                                                                                             m_material.get(),
                                                                                                                                                                             iconVertexBinding,
                                                                                                                                                                             *glBufferPool,
                                                                                                                                                                             Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Bottom));
            }
            
            GpsMarkerViewFactory::~GpsMarkerViewFactory()
            {
                Eegeo_GL(glDeleteTextures(1, &m_gpsIconTexture.textureId));
            }
            
            Eegeo::Rendering::Renderables::BatchedSpriteRenderable& GpsMarkerViewFactory::GetRenderable() const { return *m_iconRenderable; }
        }
    }
}
