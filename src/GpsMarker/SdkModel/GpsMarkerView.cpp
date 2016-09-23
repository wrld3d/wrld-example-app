// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerView.h"
#include "RenderQueue.h"
#include "BatchedSpriteRenderable.h"
#include "Colors.h"
#include "VectorMath.h"
#include "RenderCamera.h"
#include "TransformHelpers.h"
#include "RenderingModule.h"
#include "TexturedUniformColoredShader.h"
#include "TexturedUniformColoredMaterial.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "SceneModelFactory.h"
#include "WorldMeshRenderable.h"
#include "PODfile.h"
#include "PODFileParser.h"
#include "PODNode.h"
#include "PODScene.h"
#include "VertexBindingPool.h"
#include "RenderQueue.h"
#include "Model.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            namespace
            {
                const Eegeo::v4 HiddenColor = Eegeo::v4(0.4f, 0.4f, 0.4f, 1.f);
                
                const Eegeo::v4 HighlightColorDefault = Eegeo::v4(1.f, 1.f, 1.f, 1.f);
                const Eegeo::v4 HighlightColorNight = Eegeo::v4(1.f, 1.f, 0.f, 1.f);
                
                const std::string TimeNameNight = "Night";
                
                std::string GetFullMeshName(const std::string& filename, int meshId)
                {
                    std::stringstream ss;
                    ss << filename << "/meshes/" << meshId;
                    return ss.str();
                }
            }
            
            GpsMarkerView::GpsMarkerView(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                         Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                         Eegeo::Helpers::IFileIO& fileIO,
                                         Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                         Eegeo::Rendering::Renderables::BatchedSpriteRenderable& iconRenderable)
            : m_iconRenderable(iconRenderable)
            , m_transitionParam(1.0f)
            , m_scaleParam(1.0f)
            , m_visible(true)
            {
                CreateMaterials(renderingModule, textureLoader, "Sphere_8bit.pvr");
                
                ExtractRenderablesFromModelFile(renderingModule,
                                                sceneModelFactory,
                                                fileIO,
                                                "Sphere.POD");
            }
            
            GpsMarkerView::~GpsMarkerView()
            {
                Eegeo_DELETE m_pMeshRepo;
                Eegeo_DELETE m_pTriStripMeshRepo;
                
                Eegeo_DELETE m_pMarkerSphere;
                Eegeo_DELETE m_pMarkerArrow;
                Eegeo_DELETE m_pMarkerShader;
                Eegeo_DELETE m_pMarkerMaterial;
                
                Eegeo_DELETE m_pMarkerHiddenSphere;
                Eegeo_DELETE m_pMarkerHiddenArrow;
                Eegeo_DELETE m_pMarkerHiddenShader;
                Eegeo_DELETE m_pMarkerHiddenMaterial;
                
                Eegeo_DELETE m_pMarkerHighlightSphere;
                Eegeo_DELETE m_pMarkerHighlightArrow;
                Eegeo_DELETE m_pMarkerHighlightShader;
                Eegeo_DELETE m_pMarkerHighlightMaterial;
                
                Eegeo_DELETE m_pMarkerStencilClearSphere;
                Eegeo_DELETE m_pMarkerStencilClearArrow;
                Eegeo_DELETE m_pMarkerStencilClearShader;
                Eegeo_DELETE m_pMarkerStencilClearMaterial;
            }
            
            void GpsMarkerView::SetVisible(bool visible)
            {
                m_visible = visible;
            }
            
            void GpsMarkerView::SetScale(float scaleParam)
            {
                m_scaleParam = Eegeo::Math::Clamp01(scaleParam);
            }
            
            void GpsMarkerView::Update(float dt)
            {
                if(m_visible && m_transitionParam < 1.0f)
                {
                    m_transitionParam += dt * 4.0f;
                }
                else if(!m_visible && m_transitionParam > 0.0f)
                {
                    m_transitionParam -= dt * 4.0f;
                }
                m_transitionParam = Eegeo::Math::Clamp01(m_transitionParam);
                
                m_iconRenderable.Reset();
            }
            
            void GpsMarkerView::DrawIconAtEcefPosition(const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& ecefPosition)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                m_iconRenderable.SetModelViewProjection(renderCamera.GetViewProjectionMatrix());
                
                const float iconConstantScale = 0.3f;
                const float iconScale = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(renderCamera, ecefPosition) * iconConstantScale * m_transitionParam * m_scaleParam;
                
                m_iconRenderable.AddSprite(renderCamera,
                                           ecefPosition,
                                           Eegeo::v2(0, 0),
                                           Eegeo::v2(1, 1),
                                           Eegeo::Rendering::Colors::WHITE,
                                           Eegeo::v2(iconScale, iconScale));
            }
            
            void GpsMarkerView::EnqueueRenderables(const Eegeo::Rendering::RenderContext &renderContext, Eegeo::Rendering::RenderQueue &renderQueue)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                renderQueue.EnqueueRenderable(m_pMarkerSphere);
                renderQueue.EnqueueRenderable(m_pMarkerArrow);
                
                renderQueue.EnqueueRenderable(m_pMarkerHiddenSphere);
                renderQueue.EnqueueRenderable(m_pMarkerHiddenArrow);
                
                renderQueue.EnqueueRenderable(m_pMarkerHighlightSphere);
                renderQueue.EnqueueRenderable(m_pMarkerHighlightArrow);
                
                renderQueue.EnqueueRenderable(m_pMarkerStencilClearSphere);
                renderQueue.EnqueueRenderable(m_pMarkerStencilClearArrow);
            }
            
            void GpsMarkerView::SetMarkerTransform(const Eegeo::m44 &modelViewProjection, const Eegeo::m44& modelViewProjectionArrow) const
            {
                m_pMarkerSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerHiddenSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerHighlightSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerStencilClearSphere->SetModelViewProjection(modelViewProjection);
                
                m_pMarkerArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerHiddenArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerHighlightArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerStencilClearArrow->SetModelViewProjection(modelViewProjectionArrow);
            }
            
            void GpsMarkerView::SetMarkerStyle(const std::string& currentVisualMapTime) const
            {
                Eegeo::v4 highlightColor = HighlightColorDefault;
                
                if(currentVisualMapTime.compare(TimeNameNight) == 0)
                {
                    highlightColor = HighlightColorNight;
                }
                
                m_pMarkerHighlightMaterial->SetColor(highlightColor);
            }
            
            void GpsMarkerView::UpdateMarkerRenderingLayer(bool inInterior)
            {
                Eegeo::Rendering::LayerIds::Values layerId = Eegeo::Rendering::LayerIds::AfterWorldOpaque;
                
                if(inInterior)
                {
                    layerId = Eegeo::Rendering::LayerIds::AfterWorld;
                }
                
                m_pMarkerHighlightSphere->SetLayer(layerId);
                m_pMarkerHighlightArrow->SetLayer(layerId);
                
                m_pMarkerSphere->SetLayer(layerId);
                m_pMarkerArrow->SetLayer(layerId);
                
                m_pMarkerHiddenSphere->SetLayer(layerId);
                m_pMarkerHiddenArrow->SetLayer(layerId);
            }
            
            void GpsMarkerView::CreateMaterials(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                      Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                                      const std::string textureFileName)
            {
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                
                m_pMarkerHighlightShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerHighlightMaterial = Eegeo_NEW(GpsMarkerHighlightMaterial)(materialIdGenerator.GetNextId(),
                                                                                   "GpsMarkerHighlightMaterial",
                                                                                   *m_pMarkerHighlightShader,
                                                                                   HighlightColorDefault);
                
                m_pMarkerShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(shaderIdGenerator.GetNextId());
                
                Eegeo::Helpers::GLHelpers::TextureInfo markerTextureInfo;
                bool success = textureLoader.LoadTexture(markerTextureInfo, textureFileName);
                Eegeo_ASSERT(success, "Gps Marker texture file must exist");
                
                m_pMarkerMaterial = Eegeo_NEW(GpsMarkerMaterial)(materialIdGenerator.GetNextId(),
                                                                 "GpsMarkerMaterial",
                                                                 *m_pMarkerShader,
                                                                 markerTextureInfo.textureId,
                                                                 Eegeo::v4(1.f, 1.f, 1.f, 1.f));
                
                m_pMarkerHiddenShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerHiddenMaterial = Eegeo_NEW(GpsMarkerHiddenMaterial)(materialIdGenerator.GetNextId(),
                                                                             "GpsMarkerHiddenMaterial",
                                                                             *m_pMarkerHiddenShader,
                                                                             HiddenColor);
                
                m_pMarkerStencilClearShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerStencilClearMaterial = Eegeo_NEW(GpsMarkerStencilClearMaterial)(materialIdGenerator.GetNextId(),
                                                                                         "GpsMarkerStencilClearMaterial",
                                                                                         *m_pMarkerStencilClearShader,
                                                                                         Eegeo::v4(1.f, 1.f, 1.f, 1.f));
            }
            
            void GpsMarkerView::ExtractRenderablesFromModelFile(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                                      Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                                                      Eegeo::Helpers::IFileIO& fileIO,
                                                                      const std::string modelFilename)
            {
                size_t size;
                std::fstream stream;
                bool success = fileIO.OpenFile(stream, size, modelFilename, std::ifstream::in | std::ifstream::binary);
                Eegeo_ASSERT(success, "Gps Marker model file must exist");
                
                const Eegeo::IO::POD::PODFile* pPODfile = Eegeo::IO::POD::PODFileParser::ParseFileFromPODStream(stream, (u32)size);
                const Eegeo::IO::POD::PODScene* pPODScene = pPODfile->GetScene(0);
                
                m_pMeshRepo = Eegeo_NEW(Eegeo::Rendering::SceneModels::SceneModelFactory::TMeshRepo)();
                m_pTriStripMeshRepo = Eegeo_NEW(Eegeo::Rendering::SceneModels::SceneModelFactory::TTriStripMeshRepo)();
                
                sceneModelFactory.PreloadMeshesFromPodScene(*pPODScene, *m_pMeshRepo, *m_pTriStripMeshRepo, modelFilename);
                
                int nodeCount = pPODScene->GetNumOfNodes();
                
                for(int i = 0; i < nodeCount; ++i)
                {
                    const Eegeo::IO::POD::PODNode& podNode = *pPODScene->GetNode(i);
                    s32 meshId = podNode.GetMeshId();
                    
                    bool hasMesh = meshId >= 0 && i < pPODScene->GetNumMeshNodes();
                    
                    if(hasMesh)
                    {
                        std::string meshName = GetFullMeshName(modelFilename, meshId);
                        
                        bool hasMesh = m_pMeshRepo->HasResource(meshName);
                        if(hasMesh)
                        {
                            Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh = m_pMeshRepo->UseResource(meshName);
                            
                            Eegeo::Rendering::Renderables::WorldMeshRenderable* worldMeshRenderable1 = NULL;
                            Eegeo::Rendering::Renderables::WorldMeshRenderable* worldMeshRenderable2 = NULL;
                            
                            if(meshId == 0 || meshId == 2)
                            {
                                CreateMeshRenderables(mesh,
                                                      m_pMarkerHighlightShader->GetVertexAttributes(),
                                                      m_pMarkerStencilClearShader->GetVertexAttributes(),
                                                      renderingModule,
                                                      worldMeshRenderable1,
                                                      worldMeshRenderable2,
                                                      m_pMarkerHighlightMaterial,
                                                      m_pMarkerStencilClearMaterial);
                                worldMeshRenderable2->SetLayer(Eegeo::Rendering::LayerIds::AfterWorldShadow);
                                
                                if(meshId == 0)
                                {
                                    m_pMarkerHighlightSphere = worldMeshRenderable1;
                                    m_pMarkerStencilClearSphere = worldMeshRenderable2;
                                }
                                else
                                {
                                    m_pMarkerHighlightArrow = worldMeshRenderable1;
                                    m_pMarkerStencilClearArrow = worldMeshRenderable2;
                                }
                            }
                            else if(meshId == 1 || meshId == 3)
                            {
                                CreateMeshRenderables(mesh,
                                                      m_pMarkerShader->GetVertexAttributes(),
                                                      m_pMarkerHiddenShader->GetVertexAttributes(),
                                                      renderingModule,
                                                      worldMeshRenderable1,
                                                      worldMeshRenderable2,
                                                      m_pMarkerMaterial,
                                                      m_pMarkerHiddenMaterial);
                                
                                if(meshId == 1)
                                {
                                    m_pMarkerSphere = worldMeshRenderable1;
                                    m_pMarkerHiddenSphere = worldMeshRenderable2;
                                }
                                else
                                {
                                    m_pMarkerArrow = worldMeshRenderable1;
                                    m_pMarkerHiddenArrow = worldMeshRenderable2;
                                }
                                
                            }
                        }
                    }
                }
                
            }
            
            void GpsMarkerView::CreateMeshRenderables(const Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh,
                                                            const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs1,
                                                            const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs2,
                                                            const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                            Eegeo::Rendering::Renderables::WorldMeshRenderable* &meshRenderable1,
                                                            Eegeo::Rendering::Renderables::WorldMeshRenderable* &meshRenderable2,
                                                            Eegeo::Rendering::Materials::IMaterial* material1,
                                                            Eegeo::Rendering::Materials::IMaterial* material2) const
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding1 = renderingModule.GetVertexBindingPool().GetVertexBinding(mesh.GetMesh()->GetVertexLayout(), vertexAttribs1);
                
                meshRenderable1 = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorldOpaque,
                                                                                                material1,
                                                                                                vertexBinding1,
                                                                                                mesh.GetMesh(),
                                                                                                Eegeo::dv3::Zero());
                
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding2 = renderingModule.GetVertexBindingPool().GetVertexBinding(mesh.GetMesh()->GetVertexLayout(), vertexAttribs2);
                
                meshRenderable2 = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorldOpaque,
                                                                                                material2,
                                                                                                vertexBinding2,
                                                                                                mesh.GetMesh(),
                                                                                                Eegeo::dv3::Zero());
            }
        }
    }
}