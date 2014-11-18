// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiRingModule.h"

#include "PoiRingRenderable.h"
#include "PoiRingView.h"
#include "PoiRingController.h"
#include "PoiRingTouchCOntroller.h"

#include "BatchedSpriteShader.h"
#include "BatchedSpriteMaterial.h"
#include "BatchedSpriteRenderable.h"

#include "RenderableFilters.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "VertexBinding.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"

#include "LocalAsyncTextureLoader.h"

#include "TerrainRayPicker.h"
#include "TerrainHeightProvider.h"
#include "CollisionMeshResourceRepository.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"
#include "TerrainModelModule.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            PoiRingModule::PoiRingModule(IMyPinCreationModel& myPinCreationModel,
                                         Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                         Eegeo::Modules::Core::RenderingModule& renderingModule,
                                         Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule,
                                         Eegeo::Modules::Core::LightingModule& lightingModule,
                                         Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule)
            : m_renderableFilters(renderingModule.GetRenderableFilters())
            {
                m_pPoiRingRenderable = Eegeo_NEW(PoiRingRenderable)(renderingModule,
                                                                    platformAbstractions.GetFileIO(),
                                                                    asyncLoadersModule.GetLocalAsyncTextureLoader(),
                                                                    lightingModule.GetGlobalFogging());
                
                
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                m_pSpriteShader = Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator.GetNextId());
            
                platformAbstractions.GetTextureFileLoader().LoadTexture(m_poiRingIconTexture, "poi_marker.png");
                
                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                m_pPoiRingIconMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator.GetNextId(),
                                                                                                       "Poi Creation Sprite Material",
                                                                                                       *m_pSpriteShader,
                                                                                                       m_poiRingIconTexture.textureId);
                
                Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool = renderingModule.GetVertexLayoutPool();
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = renderingModule.GetVertexBindingPool();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = vertexBindingPool.GetVertexBinding(vertexLayoutPool.GetForTexturedColoredVertex(),
                                                                                                                         m_pSpriteShader->GetVertexAttributes());
                
                m_pPoiRingIconRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                                                                                             m_pPoiRingIconMaterial,
                                                                                                             iconVertexBinding,
                                                                                                             renderingModule.GetGlBufferPool(),
                                                                                                             Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Centre);
                
                
                m_pPoiRingView = Eegeo_NEW(PoiRing::PoiRingView)(*m_pPoiRingRenderable,
                                                                 *m_pPoiRingIconRenderable);
                
                m_renderableFilters.AddRenderableFilter(*m_pPoiRingView);
                
                
                m_pPoiRingController = Eegeo_NEW(PoiRingController)(myPinCreationModel,
                                                                    *m_pPoiRingView);
                
                
                m_pTerrainRayPicker = Eegeo_NEW(Eegeo::Resources::Terrain::Collision::TerrainRayPicker)(terrainModelModule.GetTerrainHeightProvider(),
                                                                                                        terrainModelModule.GetCollisionMeshResourceRepository());
                
                m_pPoiRingTouchController = Eegeo_NEW(PoiRingTouchController)(myPinCreationModel, *m_pTerrainRayPicker);
            }

            PoiRingModule::~PoiRingModule()
            {
                Eegeo_DELETE m_pPoiRingTouchController;
                Eegeo_DELETE m_pTerrainRayPicker;
                
                m_renderableFilters.RemoveRenderableFilter(*m_pPoiRingView);
                Eegeo_DELETE m_pPoiRingView;
                Eegeo_DELETE m_pPoiRingIconRenderable;
                Eegeo_DELETE m_pPoiRingIconMaterial;
                Eegeo_DELETE m_pSpriteShader;
                Eegeo_DELETE m_pPoiRingRenderable;
            }
            
            IPoiRingController& PoiRingModule::GetPoiRingController() const
            {
                return *m_pPoiRingController;
            }
            
            IPoiRingTouchController& PoiRingModule::GetPoiRingTouchController() const
            {
                return *m_pPoiRingTouchController;
            }
            

            
        }
    }
}
