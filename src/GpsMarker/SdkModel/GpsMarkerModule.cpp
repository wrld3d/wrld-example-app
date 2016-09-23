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
#include "AsyncLoadersModule.h"
#include "LocalAsyncTextureLoader.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModule::GpsMarkerModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                             Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                             Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                             Eegeo::Location::ILocationService& locationService,
                                             Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                             Eegeo::Modules::Map::MapModule& mapModule,
                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_renderableFilters(renderingModule.GetRenderableFilters())
            {
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                m_pSpriteShader = Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator.GetNextId());
                
                platformAbstractions.GetTextureFileLoader().LoadTexture(m_gpsIconTexture,
                                                                        Helpers::ImageHelpers::GetImageNameForDevice("gps_marker", ".png"),
                                                                        false);
                
                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                m_pGpsIconMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator.GetNextId(),
                                                                                                   "Gps icon Sprite Material",
                                                                                                   *m_pSpriteShader,
                                                                                                   m_gpsIconTexture.textureId,
                                                                                                   Eegeo::Rendering::TextureMinify_Nearest);
                
                Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool = renderingModule.GetVertexLayoutPool();
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = renderingModule.GetVertexBindingPool();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = vertexBindingPool.GetVertexBinding(vertexLayoutPool.GetForTexturedColoredVertex(),
                                                                                                                             m_pSpriteShader->GetVertexAttributes());
                
                m_pGpsIconRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                                                                                         m_pGpsIconMaterial,
                                                                                                         iconVertexBinding,
                                                                                                         renderingModule.GetGlBufferPool(),
                                                                                                         Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Bottom);
                
                m_pModel = Eegeo_NEW(GpsMarkerModel)(locationService, terrainModelModule.GetTerrainHeightProvider());
                m_pView = Eegeo_NEW(GpsMarkerView)(renderingModule,
                                                   sceneModelFactory,
                                                   platformAbstractions.GetFileIO(),
                                                   platformAbstractions.GetTextureFileLoader(),
                                                   *m_pGpsIconRenderable);
                m_pController = Eegeo_NEW(GpsMarkerController)(*m_pModel, *m_pView, mapModule.GetEnvironmentFlatteningService(), visualMapService, messageBus);
                
                m_renderableFilters.AddRenderableFilter(*m_pView);

            }
            
            GpsMarkerModule::~GpsMarkerModule()
            {
                m_renderableFilters.RemoveRenderableFilter(*m_pView);
                
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pGpsIconRenderable;
                Eegeo_DELETE m_pGpsIconMaterial;
                Eegeo_DELETE m_pSpriteShader;
                
                Eegeo_GL(glDeleteTextures(1, &m_gpsIconTexture.textureId));
            }
            
            IGpsMarkerController& GpsMarkerModule::GetGpsMarkerController()
            {
                return *m_pController;
            }
        }
    }
}