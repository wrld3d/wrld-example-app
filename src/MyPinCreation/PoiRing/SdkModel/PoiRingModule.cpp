// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingModule.h"

#include "PoiRingRenderable.h"
#include "PoiRingView.h"
#include "PoiRingController.h"
#include "PoiRingTouchController.h"

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
#include "MapModule.h"
#include "ImagePathHelpers.h"
#include "InteriorsPresentationModule.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingModule::PoiRingModule(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                             Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                             Eegeo::Modules::Core::RenderingModule& renderingModule,
                                             Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule,
                                             Eegeo::Modules::Core::LightingModule& lightingModule,
                                             Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                             Eegeo::Modules::Map::MapModule& mapModule,
                                             ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                             Eegeo::Rendering::ScreenProperties& screenProperties,
                                             const bool interiorsAffectedByFlattening,
                                             const bool isInKioskMode)
                    : m_renderableFilters(renderingModule.GetRenderableFilters())
                {
                    m_pPoiRingRenderable = Eegeo_NEW(PoiRingRenderable)(renderingModule,
                                           platformAbstractions.GetFileIO(),
                                           asyncLoadersModule.GetLocalAsyncTextureLoader(),
                                           lightingModule.GetGlobalFogging());


                    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                    m_pSpriteShader = Eegeo::Rendering::Shaders::BatchedSpriteShader::Create(shaderIdGenerator.GetNextId());

                    std::string iconTextureFilename;
                    if(isInKioskMode)
                    {
                        iconTextureFilename = "poi_marker@kiosk.png";
                    }
                    else
                    {
                        iconTextureFilename = Helpers::ImageHelpers::GetImageNameForDevice("poi_marker", ".png");
                    }
					
                    platformAbstractions.GetTextureFileLoader().LoadTexture(m_poiRingIconTexture,
                                                                            iconTextureFilename,
                                                                            false);

                    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                    m_pPoiRingIconMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::BatchedSpriteMaterial)(materialIdGenerator.GetNextId(),
                                             "Poi Creation Sprite Material",
                                             *m_pSpriteShader,
                                             m_poiRingIconTexture.textureId,
                                                                                                           Eegeo::Rendering::TextureMinify_Nearest);

                    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool = renderingModule.GetVertexLayoutPool();
                    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = renderingModule.GetVertexBindingPool();
                    const Eegeo::Rendering::VertexLayouts::VertexBinding& iconVertexBinding = vertexBindingPool.GetVertexBinding(vertexLayoutPool.GetForTexturedColoredVertex(),
                            m_pSpriteShader->GetVertexAttributes());

                    m_pPoiRingIconRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::BatchedSpriteRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                               m_pPoiRingIconMaterial,
                                               iconVertexBinding,
                                               renderingModule.GetGlBufferPool(),
                                               Eegeo::Rendering::Renderables::BatchedSpriteAnchor::Bottom);


                    m_pPoiRingView = Eegeo_NEW(PoiRing::SdkModel::PoiRingView)(*m_pPoiRingRenderable,
                                     *m_pPoiRingIconRenderable);

                    m_renderableFilters.AddRenderableFilter(*m_pPoiRingView);

                    
                    Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
                    
                    m_pPoiRingController = Eegeo_NEW(PoiRingController)(myPinCreationModel,
                                           *m_pPoiRingView,
                                           mapModule.GetEnvironmentFlatteningService(),
                                           terrainModelModule.GetTerrainHeightProvider(),
                                           interiorsPresentationModule.GetInteriorInteractionModel(),
                                           interiorsPresentationModule.GetInteriorTransitionModel(),
                                           screenProperties,
                                           interiorsAffectedByFlattening,
                                           isInKioskMode);


                    m_pTerrainRayPicker = Eegeo_NEW(Eegeo::Resources::Terrain::Collision::TerrainRayPicker)(terrainModelModule.GetTerrainHeightProvider(),
                                          terrainModelModule.GetCollisionMeshResourceRepository());

                    m_pPoiRingTouchController = Eegeo_NEW(PoiRingTouchController)(myPinCreationModel,
                                                                                  *m_pTerrainRayPicker,
                                                                                  *m_pPoiRingController,
                                                                                  appModeModel,
                                                                                  interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                  interiorsPresentationModule.GetInteriorTransitionModel());
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
}
