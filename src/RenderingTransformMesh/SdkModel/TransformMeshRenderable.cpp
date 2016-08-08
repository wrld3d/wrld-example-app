// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TransformMeshRenderable.h"

#include "MeshRenderable.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            TransformMeshRenderable::TransformMeshRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                                             const Eegeo::dv3& ecefPosition,
                                                             Eegeo::Rendering::Materials::IMaterial* pMaterial,
                                                             Eegeo::Rendering::Mesh* pMesh,
                                                             const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                                             bool ownMaterialAndMesh
                                                             )
            : MeshRenderable(layerId, ecefPosition, pMaterial, pMesh, vertexBinding)
            , m_transform(Eegeo::m44::CreateIdentity())
            , m_ownMaterialAndMesh(ownMaterialAndMesh)
            , m_pOwnedMaterial(pMaterial)
            , m_pOwnedMesh(pMesh)
            {
            }
            
            TransformMeshRenderable::~TransformMeshRenderable()
            {
                if(m_ownMaterialAndMesh)
                {
                    Eegeo_DELETE m_pOwnedMaterial;
                }
            }
            
            void TransformMeshRenderable::SetTransform(const Eegeo::m44& transform)
            {
                m_transform = transform;
            }
            const Eegeo::m44& TransformMeshRenderable::GetTransform() const
            {
                return m_transform;
            }
            
        }
    }
}