// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerAnchorView.h"
#include "GpsMarkerView.h"
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
				const bool RenderableOwnsMesh = false;

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
            , m_isInInterior(false)
            , m_highlightColor(GpsMarkerViewStyle::HighlightColorDefault)
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

				if(!RenderableOwnsMesh)
				{
                    Eegeo_DELETE m_pSphereMesh;
                    Eegeo_DELETE m_pCylinderMesh;
				}
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
                
                Eegeo::v4 currentHighlightColor = m_pMarkerHighlightMaterial->GetColor();
                Eegeo::v4 newHighlightColor = Eegeo::v4::Lerp(currentHighlightColor, m_highlightColor, dt);
                m_pMarkerHighlightMaterial->SetColor(newHighlightColor);
            }
            
            void GpsMarkerAnchorView::EnqueueRenderables(const Eegeo::Rendering::RenderContext &renderContext, Eegeo::Rendering::RenderQueue &renderQueue)
            {
                if(!m_visible && m_transitionParam == 0.0f)
                {
                    return;
                }
                
                if(m_isInInterior)
                {
                    renderQueue.EnqueueRenderable(m_pMarkerHighlightSphere);
                    renderQueue.EnqueueRenderable(m_pMarkerHighlightCylinder);
                
                    renderQueue.EnqueueRenderable(m_pMarkerStencilClearSphere);
                    renderQueue.EnqueueRenderable(m_pMarkerStencilClearCylinder);
                }
            }
            
            void GpsMarkerAnchorView::SetMarkerTransform(const Eegeo::m44 &modelViewProjectionSphere, const Eegeo::m44 &modelViewProjectionCylinder) const
            {
                m_pMarkerHighlightSphere->SetModelViewProjection(modelViewProjectionSphere);
                m_pMarkerHighlightCylinder->SetModelViewProjection(modelViewProjectionCylinder);
                
                m_pMarkerStencilClearSphere->SetModelViewProjection(modelViewProjectionSphere);
                m_pMarkerStencilClearCylinder->SetModelViewProjection(modelViewProjectionCylinder);
            }
            
            void GpsMarkerAnchorView::SetMarkerStyle(const std::string& currentVisualMapTime, const std::string& currentVisualMapWeather, const int environmentScale)
            {
                m_highlightColor = GpsMarkerViewStyle::HighlightColorDefault;
                
                if(environmentScale <= 0.0f && !m_isInInterior)
                {
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorFlattened;
                }
                else if(currentVisualMapTime.compare(GpsMarkerViewStyle::TimeNameNight) == 0)
                {
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorNight;
                }
                else if(currentVisualMapWeather.compare(GpsMarkerViewStyle::WeatherNameSnow) == 0)
                {
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorSnow;
                }
            }
            
            void GpsMarkerAnchorView::UpdateMarkerRenderingLayer(bool inInterior)
            {
                m_isInInterior = inInterior;
                
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
                
                m_pMarkerHighlightMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::ColorMaterial)(materialIdGenerator.GetNextId(),
                                                                                                   "GpsMarkerAnchorHighlightMaterial",
                                                                                                   *m_pMarkerHighlightShader,
                                                                                                   GpsMarkerViewStyle::HighlightColorDefault);
                
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
                            
                            GpsMarkerMeshRenderable* worldMeshRenderable1 = NULL;
                            GpsMarkerMeshRenderable* worldMeshRenderable2 = NULL;
                            
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
								m_pSphereMesh = mesh.GetMesh();

                                m_pMarkerHighlightSphere = worldMeshRenderable1;
                                m_pMarkerStencilClearSphere = worldMeshRenderable2;
                            }
                            else
                            {
								m_pCylinderMesh = mesh.GetMesh();

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
                                                            GpsMarkerMeshRenderable* &meshRenderable1,
                                                            GpsMarkerMeshRenderable* &meshRenderable2,
                                                            Eegeo::Rendering::Materials::IMaterial* material1,
                                                            Eegeo::Rendering::Materials::IMaterial* material2) const
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding1 = renderingModule.GetVertexBindingPool().GetVertexBinding(mesh.GetMesh()->GetVertexLayout(), vertexAttribs1);
                
                meshRenderable1 = Eegeo_NEW(GpsMarkerMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorldOpaque,
                                                                     material1,
                                                                     vertexBinding1,
                                                                     mesh.GetMesh(),
                                                                     Eegeo::dv3::Zero(),
                                                                     RenderableOwnsMesh);
                
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding2 = renderingModule.GetVertexBindingPool().GetVertexBinding(mesh.GetMesh()->GetVertexLayout(), vertexAttribs2);
                
                meshRenderable2 = Eegeo_NEW(GpsMarkerMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorldOpaque,
                                                                     material2,
                                                                     vertexBinding2,
                                                                     mesh.GetMesh(),
                                                                     Eegeo::dv3::Zero(),
                                                                     RenderableOwnsMesh);
            }
        }
    }
}