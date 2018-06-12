// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <platform/Modules/Core/RenderingModule.h>
#include "RenderableBase.h"
#include "Rendering.h"
#include "GpsMarker.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class AccuracyRingRenderableFactory {
            public:

                // Needs: ShaderIDGenerator, MaterialIDGenerator, GLBufferPool, VertexLayoutPool, VertexBindingPool, PositionMeshFactory, NullMaterial
                static AccuracyRingRenderableFactory* Create(Eegeo::Modules::Core::RenderingModule& renderingModule);

                AccuracyRingRenderableFactory(
                    Eegeo::Rendering::Shaders::ColorShader* pColorShader,
                    Eegeo::Rendering::Materials::ColorMaterial* pColorMaterial,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable* pSphereRenderable,
                    Eegeo::Rendering::Renderables::WorldMeshRenderable* pQuadRenderable,
                    Eegeo::Rendering::Materials::IMaterial& nullMaterial
                );
                ~AccuracyRingRenderableFactory();

                AccuracyRingRenderable* BuildRenderable();

            private:

                Eegeo::Rendering::Shaders::ColorShader* m_pColorShader;
                Eegeo::Rendering::Materials::ColorMaterial* m_pColorMaterial;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pSphereRenderable;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pQuadRenderable;
                Eegeo::Rendering::Materials::IMaterial& m_nullMaterial;
            };

        }
    }
}
