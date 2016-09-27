// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerAnchorView.h"
#include "RenderQueue.h"
#include "Colors.h"
#include "VectorMath.h"
#include "RenderCamera.h"
#include "TransformHelpers.h"
#include "RenderingModule.h"
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
            
            GpsMarkerAnchorView::GpsMarkerAnchorView(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                     Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                                     Eegeo::Helpers::IFileIO& fileIO)
            : m_transitionParam(0.0f)
            , m_scaleParam(1.0f)
            , m_visible(false)
            {
                CreateMaterials(renderingModule);
                
                ExtractRenderablesFromModelFile(renderingModule,
                                                sceneModelFactory,
                                                fileIO,
                                                "Stalk.POD");
            }
            
            GpsMarkerAnchorView::~GpsMarkerAnchorView()
            {
                Eegeo_DELETE m_pMeshRepo;
                Eegeo_DELETE m_pTriStripMeshRepo;
                
                Eegeo_DELETE m_pMarkerHighlightSphere;
                Eegeo_DELETE m_pMarkerHighlightCylinder;
                Eegeo_DELETE m_pMarkerHighlightShader;
                Eegeo_DELETE m_pMarkerHighlightMaterial;
                
                Eegeo_DELETE m_pMarkerStencilClearSphere;
                Eegeo_DELETE m_pMarkerStencilClearCylinder;
                Eegeo_DELETE m_pMarkerStencilClearShader;
                Eegeo_DELETE m_pMarkerStencilClearMaterial;
            }
            
            void GpsMarkerAnchorView::SetVisible(bool visible)
            {
                m_visible = visible;
            }
            
            void GpsMarkerAnchorView::SetScale(float scaleParam)
            {
                m_scaleParam = Eegeo::Math::Clamp01(scaleParam);
            }
            
            void GpsMarkerAnchorView::Update(float dt)
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
            }
            
            void GpsMarkerAnchorView::EnqueueRenderables(const Eegeo::Rendering::RenderContext &renderContext, Eegeo::Rendering::RenderQueue &renderQueue)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                renderQueue.EnqueueRenderable(m_pMarkerHighlightSphere);
                renderQueue.EnqueueRenderable(m_pMarkerHighlightCylinder);
                
                renderQueue.EnqueueRenderable(m_pMarkerStencilClearSphere);
                renderQueue.EnqueueRenderable(m_pMarkerStencilClearCylinder);
            }
            
            void GpsMarkerAnchorView::SetMarkerTransform(const Eegeo::m44 &modelViewProjectionSphere, const Eegeo::m44 &modelViewProjectionCylinder) const
            {
                m_pMarkerHighlightSphere->SetModelViewProjection(modelViewProjectionSphere);
                m_pMarkerHighlightCylinder->SetModelViewProjection(modelViewProjectionCylinder);
                
                m_pMarkerStencilClearSphere->SetModelViewProjection(modelViewProjectionSphere);
                m_pMarkerStencilClearCylinder->SetModelViewProjection(modelViewProjectionCylinder);
            }
            
            void GpsMarkerAnchorView::SetMarkerStyle(const std::string& currentVisualMapTime) const
            {
                Eegeo::v4 highlightColor = HighlightColorDefault;
                
                if(currentVisualMapTime.compare(TimeNameNight) == 0)
                {
                    highlightColor = HighlightColorNight;
                }
                
                m_pMarkerHighlightMaterial->SetColor(highlightColor);
            }
            
            void GpsMarkerAnchorView::UpdateMarkerRenderingLayer(bool inInterior)
            {
                Eegeo::Rendering::LayerIds::Values layerId = Eegeo::Rendering::LayerIds::AfterWorldOpaque;
                
                if(inInterior)
                {
                    layerId = Eegeo::Rendering::LayerIds::AfterWorld;
                }
                
                m_pMarkerHighlightSphere->SetLayer(layerId);
                m_pMarkerHighlightCylinder->SetLayer(layerId);
            }
            
            void GpsMarkerAnchorView::CreateMaterials(const Eegeo::Modules::Core::RenderingModule& renderingModule)
            {
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                
                m_pMarkerHighlightShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerHighlightMaterial = Eegeo_NEW(GpsMarkerHighlightMaterial)(materialIdGenerator.GetNextId(),
                                                                                   "GpsMarkerAnchorHighlightMaterial",
                                                                                   *m_pMarkerHighlightShader,
                                                                                   HighlightColorDefault);
                
                m_pMarkerStencilClearShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerStencilClearMaterial = Eegeo_NEW(GpsMarkerStencilClearMaterial)(materialIdGenerator.GetNextId(),
                                                                                         "GpsMarkerAnchorStencilClearMaterial",
                                                                                         *m_pMarkerStencilClearShader,
                                                                                         Eegeo::v4(1.f, 1.f, 1.f, 1.f));
            }
            
            void GpsMarkerAnchorView::ExtractRenderablesFromModelFile(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                                      Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                                                      Eegeo::Helpers::IFileIO& fileIO,
                                                                      const std::string modelFilename)
            {
                size_t size;
                std::fstream stream;
                bool success = fileIO.OpenFile(stream, size, modelFilename, std::ifstream::in | std::ifstream::binary);
                Eegeo_ASSERT(success, "Gps Marker Anchor model file must exist");
                
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
                                m_pMarkerHighlightCylinder = worldMeshRenderable1;
                                m_pMarkerStencilClearCylinder = worldMeshRenderable2;
                            }
                        }
                    }
                }
                
            }
            
            void GpsMarkerAnchorView::CreateMeshRenderables(const Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh,
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