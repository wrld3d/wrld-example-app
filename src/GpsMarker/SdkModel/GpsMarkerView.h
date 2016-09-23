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
#include "GpsMarkerMaterial.h"
#include "GpsMarkerHiddenMaterial.h"
#include "GpsMarkerHighlightMaterial.h"
#include "GpsMarkerStencilClearMaterial.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
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
                void SetMarkerStyle(const std::string& currentVisualMapTime) const;
                void UpdateMarkerRenderingLayer(bool inInterior);
                
            private:
                
                Eegeo::Rendering::Renderables::BatchedSpriteRenderable& m_iconRenderable;
                bool m_visible;
                float m_transitionParam;
                float m_scaleParam;
                
                Eegeo::Rendering::SceneModels::SceneModelFactory::TMeshRepo* m_pMeshRepo;
                Eegeo::Rendering::SceneModels::SceneModelFactory::TTriStripMeshRepo* m_pTriStripMeshRepo;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerArrow;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pMarkerShader;
                GpsMarkerMaterial* m_pMarkerMaterial;
                
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
                                     const std::string textureFilename);
                
                void ExtractRenderablesFromModelFile(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                     Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                                     Eegeo::Helpers::IFileIO& fileIO,
                                                     const std::string modelFilename);
                
                void CreateMeshRenderables(const Eegeo::Rendering::SceneModels::SceneModelMeshResource& mesh,
                                           const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs1,
                                           const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttribs2,
                                           const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                           Eegeo::Rendering::Renderables::WorldMeshRenderable* &meshRenderable1,
                                           Eegeo::Rendering::Renderables::WorldMeshRenderable* &meshRenderable2,
                                           Eegeo::Rendering::Materials::IMaterial* material1,
                                           Eegeo::Rendering::Materials::IMaterial* material2) const;
            };
        }
    }
}