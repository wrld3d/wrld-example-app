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
                    const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                    const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                    const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                    const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                    const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool);

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

