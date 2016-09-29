// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "Rendering.h"
#include "VectorMathDecl.h"
#include "Camera.h"
#include "IFileIO.h"
#include "Modules.h"
#include "SceneModelFactory.h"
#include "RenderCamera.h"
#include "GpsMarkerShader.h"
#include "GpsMarkerMaterial.h"
#include "GpsMarkerNotHiddenMaterial.h"
#include "GpsMarkerHiddenMaterial.h"
#include "GpsMarkerHighlightMaterial.h"
#include "GpsMarkerStencilClearMaterial.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            namespace GpsMarkerViewStyle
            {
                const Eegeo::v4 HiddenColor = Eegeo::v4(0.3f, 0.3f, 0.3f, 0.5f);
                
                const Eegeo::v4 HighlightColorDefault = Eegeo::v4(1.f, 1.f, 1.f, 1.f);
                const Eegeo::v4 HighlightColorNight = Eegeo::v4(1.f, 0.78f, 0.13f, 1.f);
                const Eegeo::v4 HighlightColorSnow = Eegeo::v4(0.54f, 1.f, 1.f, 1.f);
                const Eegeo::v4 HighlightColorFlattened = Eegeo::v4(0.07f, 0.34f, 0.69f, 1.f);
                
                const Eegeo::v4 MainColorFlattened = Eegeo::v4(0.04f, 0.68f, 1.f, 1.f);
                
                const std::string TimeNameNight = "Night";
                const std::string WeatherNameSnow = "Snowy";
            }
            
            class GpsMarkerView : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                
                GpsMarkerView(Eegeo::Modules::Core::RenderingModule& renderingModule,
                              Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                              Eegeo::Helpers::IFileIO& fileIO,
                              Eegeo::Helpers::ITextureFileLoader& textureLoader,
                              Eegeo::Rendering::Renderables::BatchedSpriteRenderable& iconRenderable);
                ~GpsMarkerView();
                
                void SetVisible(bool visible);
                void SetScale(float scaleParam);
                void Update(float dt);
                void DrawIconAtEcefPosition(const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& ecefPosition);
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                void SetMarkerTransform(const Eegeo::m44& modelViewProjection, const Eegeo::m44& modelViewProjectionArrow) const;
                void SetMarkerStyle(const std::string& currentVisualMapTime, const std::string& currentVisualMapWeather, const int environmentScale);
                void UpdateMarkerRenderingLayer(bool inInterior);
                
            private:
                
                Eegeo::Rendering::Renderables::BatchedSpriteRenderable& m_iconRenderable;
                bool m_visible;
                float m_transitionParam;
                float m_scaleParam;
                bool m_isInInterior;
                
                Eegeo::v4 m_highlightColor;
                Eegeo::v4 m_hiddenColor;
                float m_colorLerpValue;
                float m_textureLerpValue;
                
                Eegeo::Rendering::SceneModels::SceneModelFactory::TMeshRepo* m_pMeshRepo;
                Eegeo::Rendering::SceneModels::SceneModelFactory::TTriStripMeshRepo* m_pTriStripMeshRepo;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerArrow;
                GpsMarkerShader* m_pMarkerShader;
                GpsMarkerMaterial* m_pMarkerMaterial;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerNotHiddenSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerNotHiddenArrow;
                GpsMarkerShader* m_pMarkerNotHiddenShader;
                GpsMarkerNotHiddenMaterial* m_pMarkerNotHiddenMaterial;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHiddenSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHiddenArrow;
                Eegeo::Rendering::Shaders::ColorShader* m_pMarkerHiddenShader;
                GpsMarkerHiddenMaterial* m_pMarkerHiddenMaterial;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHighlightSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHighlightArrow;
                Eegeo::Rendering::Shaders::ColorShader* m_pMarkerHighlightShader;
                GpsMarkerHighlightMaterial* m_pMarkerHighlightMaterial;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerStencilClearSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerStencilClearArrow;
                Eegeo::Rendering::Shaders::ColorShader* m_pMarkerStencilClearShader;
                GpsMarkerStencilClearMaterial* m_pMarkerStencilClearMaterial;
                
                void CreateMaterials(const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                     Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                     const std::string textureFilenameDay,
                                     const std::string textureFilenameNight);
                
                void ExtractRenderablesFromModelFile(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                     Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                                     Eegeo::Helpers::IFileIO& fileIO,
                                                     const std::string modelFilename);
                
                void CreateMeshRenderables(const Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh,
                                           const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                           const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs,
                                           Eegeo::Rendering::Renderables::WorldMeshRenderable* &meshRenderable,
                                           Eegeo::Rendering::Materials::IMaterial* material) const;
            };
        }
    }
}