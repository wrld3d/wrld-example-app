// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundNativeView.h"
#include "Colors.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Mesh.h"
#include "Quad.h"
#include "GLBufferPool.h"
#include "VertexLayoutPool.h"
#include "VertexBinding.h"
#include "WorldMeshRenderable.h"
#include "VectorMath.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            ModalBackgroundNativeView::ModalBackgroundNativeView(
                    const std::shared_ptr<Eegeo::Rendering::Shaders::ShaderIdGenerator>& shaderIdGenerator,
                    const std::shared_ptr<Eegeo::Rendering::Materials::MaterialIdGenerator>& materialIdGenerator,
                    const std::shared_ptr<Eegeo::Rendering::GlBufferPool>& glBufferPool,
                    const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>& vertexLayoutPool,
                    const std::shared_ptr<Eegeo::Rendering::VertexLayouts::VertexBindingPool>& vertexBindingPool)
            : m_fixedOn(false)
            , m_fixedTransition(0.0f)
            , m_setAlpha(0.0f)
            {
                ASSERT_NATIVE_THREAD

                m_shader = std::shared_ptr<Eegeo::Rendering::Shaders::ColorShader>(Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator->GetNextId()));

                m_material = std::make_shared<Eegeo::Rendering::Materials::ColorMaterial>(materialIdGenerator->GetNextId(),
                              "ModelBackgrounal",
                              *m_shader,
                              Eegeo::v4::Zero());

                Eegeo::Rendering::Mesh* pScreenQuad = Eegeo::Rendering::Geometry::CreatePositionQuad(*glBufferPool, *vertexLayoutPool);

                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool->GetVertexBinding(
                            pScreenQuad->GetVertexLayout(),
                            m_material->GetShader().GetVertexAttributes());

                m_modalBackgroundRenderable = std::make_shared<Eegeo::Rendering::Renderables::WorldMeshRenderable>(
                                                   Eegeo::Rendering::LayerIds::AfterAll, m_material.get(), vertexBinding, pScreenQuad, Eegeo::dv3::Zero());
                m_modalBackgroundRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

                m_baseAlpha = 0.46f;
                SetAlpha(0.0f);
            }

            ModalBackgroundNativeView::~ModalBackgroundNativeView()
            {
            }

            void ModalBackgroundNativeView::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
            {
                ASSERT_NATIVE_THREAD

                if(m_material->GetColor().w > 0.0f)
                {
                    renderQueue.EnqueueRenderable(*m_modalBackgroundRenderable);
                }
            }

            void ModalBackgroundNativeView::SetAlpha(float alpha)
            {
                ASSERT_NATIVE_THREAD

                m_setAlpha = alpha;
            }

            void ModalBackgroundNativeView::SetFixedOn(bool fixedOn)
            {
            	m_fixedOn = fixedOn;
            }

            void ModalBackgroundNativeView::Update(float dt)
            {
            	dt = std::min(dt, 0.05f);
            	m_fixedTransition = m_fixedOn ? m_fixedTransition+dt : m_fixedTransition-dt;
            	m_fixedTransition = Eegeo::Math::Clamp01(m_fixedTransition);

            	float trueAlpha = Eegeo::Math::Lerp(m_setAlpha, 1.0f, m_fixedTransition);

            	Eegeo::v4 color(0.0f, 0.0f, 0.0f, trueAlpha * m_baseAlpha);
            	m_material->SetColor(color);
            }
        }
    }
}
