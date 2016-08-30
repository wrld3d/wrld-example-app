// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModule.h"
#include "ShaderIdGenerator.h"
#include "RenderingModule.h"
#include "BatchedSpriteShader.h"
#include "MaterialIdGenerator.h"
#include "BatchedSpriteMaterial.h"
#include "BatchedSpriteRenderable.h"
#include "IPlatformAbstractionModule.h"
#include "ITextureFileLoader.h"
#include "VertexBindingPool.h"
#include "VertexLayoutPool.h"
#include "GpsMarkerView.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerController.h"
#include "RenderableFilters.h"
#include "TerrainModelModule.h"
#include "ImagePathHelpers.h"
#include "MapModule.h"
#include "ILocationService.h"
#include "TerrainHeightProvider.h"
#include "GlBufferPool.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {   
            GpsMarkerModule::~GpsMarkerModule()
            {
                Eegeo_GL(glDeleteTextures(1, &m_gpsIconTexture.textureId));
            }
            
            void GpsMarkerModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<GpsMarkerModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::shared_ptr<Eegeo::Rendering::Shaders::BatchedSpriteShader>(Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(context.resolve<Eegeo::Rendering::Shaders::ShaderIdGenerator>()->GetNextId()));
                                                   }).singleInstance();
                
                builder->registerInstanceFactory([this](Hypodermic::ComponentContext& context)
                                                   {
                                                       context.resolve<Eegeo::Helpers::ITextureFileLoader>()->LoadTexture(m_gpsIconTexture,
                                                                                                                          Helpers::ImageHelpers::GetImageNameForDevice("gps_marker", ".png"),
                                                                                                                          false);
                                                       return std::make_shared<Eegeo::Rendering::Materials::BatchedSpriteMaterial>(
                                                                                       context.resolve<Eegeo::Rendering::Materials::MaterialIdGenerator>()->GetNextId(),
                                                                                       "Gps icon Sprite Material",
                                                                                       *(context.resolve<Eegeo::Rendering::Shaders::BatchedSpriteShader>()),
                                                                                       m_gpsIconTexture.textureId,
                                                                                       Eegeo::Rendering::TextureMinify_Nearest);
                                                   }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = context.resolve<Eegeo::Rendering::VertexLayouts::VertexBindingPool>()->GetVertexBinding(context.resolve<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>()->GetForTexturedColoredVertex(),
                                                                                                                                                                    context.resolve<Eegeo::Rendering::Shaders::BatchedSpriteShader>()->GetVertexAttributes());
                                                       return std::make_shared<Eegeo::Rendering::Renderables::BatchedSpriteRenderable>(Eegeo::Rendering::LayerIds::AfterAll,
                                                                                                                                       context.resolve<Eegeo::Rendering::Materials::BatchedSpriteMaterial>().get(),
                                                                                                                                       iconVertexBinding,
                                                                                                                                       *(context.resolve<Eegeo::Rendering::GlBufferPool>()),
                                                                                                                                       Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Bottom);
                                                   }
                                                   ).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<GpsMarkerView>(*(context.resolve<Eegeo::Rendering::Renderables::BatchedSpriteRenderable>()));
                                                   }).singleInstance();
                builder->registerType<GpsMarkerController>().as<IGpsMarkerController>().singleInstance();
            }
        }
    }
}