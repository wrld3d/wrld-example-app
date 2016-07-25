// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MeshRenderable.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            class TransformMeshRenderable : public Eegeo::Rendering::Renderables::MeshRenderable
            {
            public:
                TransformMeshRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                        const Eegeo::dv3& ecefPosition,
                                        Eegeo::Rendering::Materials::IMaterial* pMaterial,
                                        Eegeo::Rendering::Mesh* pMesh,
                                        const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                        bool ownMaterialAndMesh = false);
                
                ~TransformMeshRenderable();
                
                void SetTransform(const Eegeo::m44& transform);
                const Eegeo::m44& GetTransform() const;
                
            private:
                Eegeo::m44 m_transform;
                bool m_ownMaterialAndMesh;
                Eegeo::Rendering::Materials::IMaterial* m_pOwnedMaterial;
                Eegeo::Rendering::Mesh* m_pOwnedMesh;
            };
        }
    }
}