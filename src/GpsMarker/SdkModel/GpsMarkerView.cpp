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
            
            GpsMarkerView::GpsMarkerView(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                         Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                         Eegeo::Helpers::IFileIO& fileIO,
                                         Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                         Eegeo::Rendering::Renderables::BatchedSpriteRenderable& iconRenderable)
            : m_iconRenderable(iconRenderable)
            , m_transitionParam(0.0f)
            , m_scaleParam(1.0f)
            , m_visible(false)
            , m_isInInterior(false)
            , m_highlightColor(GpsMarkerViewStyle::HighlightColorDefault)
            , m_hiddenColor(GpsMarkerViewStyle::HiddenColor)
            , m_colorLerpValue(0)
            , m_textureLerpValue(0)
            {
                CreateMaterials(renderingModule, textureLoader, "Sphere_8bit", "Sphere_Night_8bit");
                
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
                
                Eegeo_DELETE m_pMarkerNotHiddenSphere;
                Eegeo_DELETE m_pMarkerNotHiddenArrow;
                Eegeo_DELETE m_pMarkerNotHiddenShader;
                Eegeo_DELETE m_pMarkerNotHiddenMaterial;
                
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

				if(!RenderableOwnsMesh)
				{
                    Eegeo_DELETE m_pSphereMesh;
                    Eegeo_DELETE m_pArrowMesh;
                    Eegeo_DELETE m_pSphereHighlightMesh;
                    Eegeo_DELETE m_pArrowHighlightMesh;
				}
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
                
                float currentColorLerpValue = m_pMarkerMaterial->GetColorLerpValue();
                float newColorLerpValue = Eegeo::Math::Lerp(currentColorLerpValue, m_colorLerpValue, dt);
                m_pMarkerMaterial->SetColorLerpValue(newColorLerpValue);
                m_pMarkerNotHiddenMaterial->SetColorLerpValue(newColorLerpValue);
                
                float currentTextureLerpValue = m_pMarkerMaterial->GetTextureLerpValue();
                float newTextureLerpValue = Eegeo::Math::Lerp(currentTextureLerpValue, m_textureLerpValue, dt);
                m_pMarkerMaterial->SetTextureLerpValue(newTextureLerpValue);
                m_pMarkerNotHiddenMaterial->SetTextureLerpValue(newTextureLerpValue);
                
                Eegeo::v4 currentHiddenColor = m_pMarkerHiddenMaterial->GetColor();
                Eegeo::v4 newHiddenColor = Eegeo::v4::Lerp(currentHiddenColor, m_hiddenColor, dt);
                m_pMarkerHiddenMaterial->SetColor(newHiddenColor);
                
                Eegeo::v4 currentHighlightColor = m_pMarkerHighlightMaterial->GetColor();
                Eegeo::v4 newHighlightColor = Eegeo::v4::Lerp(currentHighlightColor, m_highlightColor, dt);
                m_pMarkerHighlightMaterial->SetColor(newHighlightColor);
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
                
                renderQueue.EnqueueRenderable(m_pMarkerNotHiddenSphere);
                renderQueue.EnqueueRenderable(m_pMarkerNotHiddenArrow);
                
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
                m_pMarkerNotHiddenSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerHiddenSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerHighlightSphere->SetModelViewProjection(modelViewProjection);
                m_pMarkerStencilClearSphere->SetModelViewProjection(modelViewProjection);
                
                m_pMarkerArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerNotHiddenArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerHiddenArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerHighlightArrow->SetModelViewProjection(modelViewProjectionArrow);
                m_pMarkerStencilClearArrow->SetModelViewProjection(modelViewProjectionArrow);
            }
            
            void GpsMarkerView::SetMarkerStyle(const std::string& currentVisualMapTime, const std::string& currentVisualMapWeather, const int environmentScale)
            {
                m_colorLerpValue = 0;
                m_textureLerpValue = 0;
                m_hiddenColor = GpsMarkerViewStyle::HiddenColor;
                m_highlightColor = GpsMarkerViewStyle::HighlightColorDefault;
                
                if(environmentScale <= 0.0f && !m_isInInterior)
                {
                    m_colorLerpValue = 1;
                    m_hiddenColor = GpsMarkerViewStyle::MainColorFlattened;
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorFlattened;
                }
                else if(currentVisualMapTime.compare(GpsMarkerViewStyle::TimeNameNight) == 0)
                {
                    m_textureLerpValue = 1;
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorNight;
                }
                else if(currentVisualMapWeather.compare(GpsMarkerViewStyle::WeatherNameSnow) == 0)
                {
                    m_highlightColor = GpsMarkerViewStyle::HighlightColorSnow;
                }
            }
            
            void GpsMarkerView::UpdateMarkerRenderingLayer(bool inInterior)
            {
                m_isInInterior = inInterior;
                
                Eegeo::Rendering::LayerIds::Values layerId = Eegeo::Rendering::LayerIds::AfterWorldOpaque;
                
                m_pMarkerHighlightSphere->SetLayer(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
                m_pMarkerHighlightArrow->SetLayer(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
                
                if(inInterior)
                {
                    layerId = Eegeo::Rendering::LayerIds::AfterWorld;
                    
                    m_pMarkerHighlightSphere->SetLayer(layerId);
                    m_pMarkerHighlightArrow->SetLayer(layerId);
                }
                
                m_pMarkerSphere->SetLayer(layerId);
                m_pMarkerArrow->SetLayer(layerId);
                
                m_pMarkerNotHiddenSphere->SetLayer(layerId);
                m_pMarkerNotHiddenArrow->SetLayer(layerId);
                
                m_pMarkerHiddenSphere->SetLayer(layerId);
                m_pMarkerHiddenArrow->SetLayer(layerId);
            }
            
            void GpsMarkerView::CreateMaterials(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                                const std::string textureFileNameDay,
                                                const std::string textureFileNameNight)
            {
                Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator = renderingModule.GetShaderIdGenerator();
                Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator = renderingModule.GetMaterialIdGenerator();
                
                m_pMarkerHighlightShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerHighlightMaterial = Eegeo_NEW(GpsMarkerHighlightMaterial)(materialIdGenerator.GetNextId(),
                                                                                   "GpsMarkerHighlightMaterial",
                                                                                   *m_pMarkerHighlightShader,
                                                                                   GpsMarkerViewStyle::HighlightColorDefault);
                
                m_pMarkerShader = GpsMarkerShader::Create(shaderIdGenerator.GetNextId());
                
                Eegeo::Helpers::GLHelpers::TextureInfo markerDayTextureInfo;
                bool successDay = textureLoader.LoadTexture(markerDayTextureInfo, textureFileNameDay);
                Eegeo_ASSERT(successDay, "Gps Marker Day texture file must exist");
                
                Eegeo::Helpers::GLHelpers::TextureInfo markerNightTextureInfo;
                bool successNight = textureLoader.LoadTexture(markerNightTextureInfo, textureFileNameNight);
                Eegeo_ASSERT(successNight, "Gps Marker Night texture file must exist");
                
                m_pMarkerMaterial = Eegeo_NEW(GpsMarkerMaterial)(materialIdGenerator.GetNextId(),
                                                                 "GpsMarkerMaterial",
                                                                 *m_pMarkerShader,
                                                                 markerDayTextureInfo.textureId,
                                                                 markerNightTextureInfo.textureId,
                                                                 GpsMarkerViewStyle::MainColorFlattened);
                
                m_pMarkerNotHiddenShader = GpsMarkerShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerNotHiddenMaterial = Eegeo_NEW(GpsMarkerNotHiddenMaterial)(materialIdGenerator.GetNextId(),
                                                                                   "GpsMarkerNotHiddenMaterial",
                                                                                   *m_pMarkerNotHiddenShader,
                                                                                   markerDayTextureInfo.textureId,
                                                                                   markerNightTextureInfo.textureId,
                                                                                   GpsMarkerViewStyle::MainColorFlattened);
                
                m_pMarkerHiddenShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());
                
                m_pMarkerHiddenMaterial = Eegeo_NEW(GpsMarkerHiddenMaterial)(materialIdGenerator.GetNextId(),
                                                                             "GpsMarkerHiddenMaterial",
                                                                             *m_pMarkerHiddenShader,
                                                                             GpsMarkerViewStyle::HiddenColor);
                
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
                            
                            if(meshId == 0 || meshId == 2)
                            {
                                GpsMarkerMeshRenderable* gpsMarkerMeshRenderable = NULL;
                                CreateMeshRenderables(mesh,
                                                      renderingModule,
                                                      m_pMarkerHighlightShader->GetVertexAttributes(),
                                                      gpsMarkerMeshRenderable,
                                                      m_pMarkerHighlightMaterial);
                                gpsMarkerMeshRenderable->SetLayer(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
                                
                                if(meshId == 0)
                                {
                                    m_pSphereHighlightMesh = mesh.GetMesh();

                                    m_pMarkerHighlightSphere = gpsMarkerMeshRenderable;
                                }
                                else
                                {
                                    m_pArrowHighlightMesh = mesh.GetMesh();

                                    m_pMarkerHighlightArrow = gpsMarkerMeshRenderable;
                                }
                            }
                            else if(meshId == 1 || meshId == 3)
                            {
                                GpsMarkerMeshRenderable* gpsMarkerMeshRenderable1 = NULL;
                                CreateMeshRenderables(mesh,
                                                      renderingModule,
                                                      m_pMarkerShader->GetVertexAttributes(),
                                                      gpsMarkerMeshRenderable1,
                                                      m_pMarkerMaterial);
                                
                                GpsMarkerMeshRenderable* gpsMarkerMeshRenderable2 = NULL;
                                CreateMeshRenderables(mesh,
                                                      renderingModule,
                                                      m_pMarkerNotHiddenShader->GetVertexAttributes(),
                                                      gpsMarkerMeshRenderable2,
                                                      m_pMarkerNotHiddenMaterial);
                                
                                GpsMarkerMeshRenderable* gpsMarkerMeshRenderable3 = NULL;
                                CreateMeshRenderables(mesh,
                                                      renderingModule,
                                                      m_pMarkerHiddenShader->GetVertexAttributes(),
                                                      gpsMarkerMeshRenderable3,
                                                      m_pMarkerHiddenMaterial);
                                
                                GpsMarkerMeshRenderable* gpsMarkerMeshRenderable4 = NULL;
                                CreateMeshRenderables(mesh,
                                                      renderingModule,
                                                      m_pMarkerStencilClearShader->GetVertexAttributes(),
                                                      gpsMarkerMeshRenderable4,
                                                      m_pMarkerStencilClearMaterial);
                                gpsMarkerMeshRenderable4->SetLayer(Eegeo::Rendering::LayerIds::AfterWorldShadow);
                                
                                if(meshId == 1)
                                {
                                    m_pSphereMesh = mesh.GetMesh();

                                    m_pMarkerSphere = gpsMarkerMeshRenderable1;
                                    m_pMarkerNotHiddenSphere = gpsMarkerMeshRenderable2;
                                    m_pMarkerHiddenSphere = gpsMarkerMeshRenderable3;
                                    m_pMarkerStencilClearSphere = gpsMarkerMeshRenderable4;
                                }
                                else
                                {
                                    m_pArrowMesh = mesh.GetMesh();

                                    m_pMarkerArrow = gpsMarkerMeshRenderable1;
                                    m_pMarkerNotHiddenArrow = gpsMarkerMeshRenderable2;
                                    m_pMarkerHiddenArrow = gpsMarkerMeshRenderable3;
                                    m_pMarkerStencilClearArrow = gpsMarkerMeshRenderable4;
                                }
                            }
                        }
                    }
                }
            }
            
            void GpsMarkerView::CreateMeshRenderables(const Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh,
                                                      const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                      const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs,
                                                      GpsMarkerMeshRenderable* &meshRenderable,
                                                      Eegeo::Rendering::Materials::IMaterial* material) const
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = renderingModule.GetVertexBindingPool().GetVertexBinding(mesh.GetMesh()->GetVertexLayout(), vertexAttribs);
                
                meshRenderable = Eegeo_NEW(GpsMarkerMeshRenderable)(Eegeo::Rendering::LayerIds::AfterWorldOpaque,
                                                                    material,
                                                                    vertexBinding,
                                                                    mesh.GetMesh(),
                                                                    Eegeo::dv3::Zero(),
                                                                    RenderableOwnsMesh);
            }
        }
    }
}