/*
 * ModelVackgroundView.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: eegeo
 */

#include "ModalBackgroundView.h"
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

namespace ExampleApp
{
	namespace ModalBackground
	{
		ModalBackgroundView::ModalBackgroundView(
				Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
				Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
				Eegeo::Rendering::GlBufferPool& glBufferPool,
				Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
				Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
		{
    		ASSERT_NATIVE_THREAD

			m_pShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderIdGenerator.GetNextId());

			m_pMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::ColorMaterial)(materialIdGenerator.GetNextId(),
																		"ModelBackgrounal",
																		*m_pShader,
																		Eegeo::v4::Zero());

			Eegeo::Rendering::Mesh* pScreenQuad = Eegeo::Rendering::Geometry::CreatePositionQuad(glBufferPool, vertexLayoutPool);

			const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(
					pScreenQuad->GetVertexLayout(),
					m_pMaterial->GetShader().GetVertexAttributes());

			m_pModalBackgroundRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::WorldMeshRenderable)(
					Eegeo::Rendering::LayerIds::ShadowOverlay, m_pMaterial, vertexBinding, pScreenQuad, Eegeo::dv3::Zero());
			m_pModalBackgroundRenderable->SetModelViewProjection(Eegeo::m44::CreateIdentity());

			m_baseAlpha = 0.46f;
			SetAlpha(0.0f);
		}

		ModalBackgroundView::~ModalBackgroundView()
		{
    		ASSERT_NATIVE_THREAD

			Eegeo_DELETE m_pModalBackgroundRenderable;
			Eegeo_DELETE m_pMaterial;
			Eegeo_DELETE m_pShader;
		}

		void ModalBackgroundView::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
		{
    		ASSERT_NATIVE_THREAD

			if(m_pMaterial->GetColor().w > 0.0f)
			{
				renderQueue.EnqueueRenderable(m_pModalBackgroundRenderable);
			}
		}

		void ModalBackgroundView::SetAlpha(float alpha)
		{
    		ASSERT_NATIVE_THREAD

			Eegeo::v4 color(0.0f, 0.0f, 0.0f, alpha * m_baseAlpha);
			m_pMaterial->SetColor(color);
		}

	}
}
