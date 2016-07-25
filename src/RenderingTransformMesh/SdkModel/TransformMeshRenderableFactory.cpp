// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TransformMeshRenderableFactory.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            TransformMeshRenderableFactory::TransformMeshRenderableFactory(Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
            : m_vertexBindingPool(vertexBindingPool)
            {
            }
            
            TransformMeshRenderable* TransformMeshRenderableFactory::CreateTransformMeshRenderable(Eegeo::Rendering::Mesh* pMesh, Eegeo::Rendering::Materials::IMaterial* pMaterial, const Eegeo::dv3 ecefPosition, const Eegeo::Rendering::LayerIds::Values renderLayer, bool ownMaterialAndMesh)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
                m_vertexBindingPool.GetVertexBinding(pMesh->GetVertexLayout(), pMaterial->GetShader().GetVertexAttributes());
                
                return Eegeo_NEW(TransformMeshRenderable)(renderLayer,
                                                          ecefPosition,
                                                          pMaterial,
                                                          pMesh,
                                                          vertexBinding,
                                                          ownMaterialAndMesh
                                                          );
            }
        }
    }
}