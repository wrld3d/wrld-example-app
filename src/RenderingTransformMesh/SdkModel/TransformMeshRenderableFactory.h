// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "TransformMeshRenderable.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class TransformMeshRenderableFactory : Eegeo::NonCopyable
            {
            private:
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            public:
                TransformMeshRenderableFactory(Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);
                
                TransformMeshRenderable* CreateTransformMeshRenderable(Eegeo::Rendering::Mesh* pMesh, Eegeo::Rendering::Materials::IMaterial* pMaterial, const Eegeo::dv3 ecefPosition, const Eegeo::Rendering::LayerIds::Values renderLayer, bool ownMaterialAndMesh = false);
            };
        }
    }
}
