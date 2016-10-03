// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "WorldMeshRenderable.h"
#include "LayerIds.h"
#include "Rendering.h"
#include "VectorMath.h"

namespace ExampleApp
{
	namespace GpsMarker
	{
		namespace SdkModel
		{
			class GpsMarkerMeshRenderable : public Eegeo::Rendering::Renderables::WorldMeshRenderable
			{
			public:
				GpsMarkerMeshRenderable(Eegeo::Rendering::LayerIds::Values layerId,
					Eegeo::Rendering::Materials::IMaterial* material,
					const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
					Eegeo::Rendering::Mesh* pMesh,
					Eegeo::dv3 ecefPosition,
					bool ownsMesh)
				: WorldMeshRenderable(layerId, material, vertexBinding, pMesh, ecefPosition)
				, m_ownsMesh(ownsMesh)
				{
				}

				~GpsMarkerMeshRenderable()
				{
					if(!m_ownsMesh)
					{
						m_pMesh = NULL;
					}
				}

			private:
				bool m_ownsMesh;
			};
		}
	}
}