// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "IRenderableFilter.h"

namespace ExampleApp
{
	namespace ModalBackground
	{
		class ModalBackgroundView : public Eegeo::Rendering::IRenderableFilter
		{
		public:
			ModalBackgroundView(
			    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
			    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
			    Eegeo::Rendering::GlBufferPool& glBufferPool,
			    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
			    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);

			virtual ~ModalBackgroundView();

			void SetAlpha(float alpha);

			void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);

		private:

			Eegeo::Rendering::Shaders::ColorShader* m_pShader;
			Eegeo::Rendering::Materials::ColorMaterial* m_pMaterial;
			Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pModalBackgroundRenderable;
			float m_baseAlpha;
		};
	}
}

