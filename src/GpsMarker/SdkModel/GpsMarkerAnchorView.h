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
#include "GpsMarkerHighlightMaterial.h"
#include "GpsMarkerStencilClearMaterial.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerAnchorView : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                GpsMarkerAnchorView(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                    Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                    Eegeo::Helpers::IFileIO& fileIO);
                ~GpsMarkerAnchorView();
                
                void SetVisible(bool visible);
                void SetScale(float scaleParam);
                void Update(float dt);
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                void SetMarkerTransform(const Eegeo::m44& modelViewProjectionSphere, const Eegeo::m44& modelViewProjectionCylinder) const;
                void SetMarkerStyle(const std::string& currentVisualMapTime, const std::string& currentVisualMapWeather, const int environmentScale);
                void UpdateMarkerRenderingLayer(bool inInterior);
                
            private:
                bool m_visible;
                float m_transitionParam;
                float m_scaleParam;
                bool m_isInInterior;
                Eegeo::v4 m_highlightColor;
                
                Eegeo::Rendering::SceneModels::SceneModelFactory::TMeshRepo* m_pMeshRepo;
                Eegeo::Rendering::SceneModels::SceneModelFactory::TTriStripMeshRepo* m_pTriStripMeshRepo;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHighlightSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerHighlightCylinder;
                Eegeo::Rendering::Shaders::ColorShader* m_pMarkerHighlightShader;
                Eegeo::Rendering::Materials::ColorMaterial* m_pMarkerHighlightMaterial;
                
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerStencilClearSphere;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pMarkerStencilClearCylinder;
                Eegeo::Rendering::Shaders::ColorShader* m_pMarkerStencilClearShader;
                GpsMarkerStencilClearMaterial* m_pMarkerStencilClearMaterial;
                
                void CreateMaterials(const Eegeo::Modules::Core::RenderingModule& renderingModule);
                
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