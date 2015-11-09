// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "IRenderableFilter.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            class ModalBackgroundNativeView : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                ModalBackgroundNativeView(
                    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                    Eegeo::Rendering::GlBufferPool& glBufferPool,
                    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);

                virtual ~ModalBackgroundNativeView();

                void SetFixedOn(bool fixedOn);
                void Update(float dt);
                void SetAlpha(float alpha);

                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);

            private:

                bool m_fixedOn;
                float m_fixedTransition;
                float m_setAlpha;

                Eegeo::Rendering::Shaders::ColorShader* m_pShader;
                Eegeo::Rendering::Materials::ColorMaterial* m_pMaterial;
                Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pModalBackgroundRenderable;
                float m_baseAlpha;
            };
        }
    }
}

