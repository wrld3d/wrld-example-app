// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PostProcessVignetteRenderable__
#define __ExampleApp__PostProcessVignetteRenderable__

#include "MeshRenderable.h"
#include "Rendering.h"
#include "VectorMathDecl.h"

namespace Examples
{
    class PostProcessVignetteRenderable : public Eegeo::Rendering::Renderables::MeshRenderable
    {
    public:
        PostProcessVignetteRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                      Eegeo::Rendering::Materials::IMaterial* material,
                                      const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                      Eegeo::Rendering::Mesh* pMesh)
        : MeshRenderable(layerId, Eegeo::dv3(), material, pMesh, vertexBinding)
        , m_radiusModifier(0.f)
        , m_colour(0.f, 0.f, 0.f)
        {
            
        }
        
        virtual void Render(Eegeo::Rendering::GLState& glState) const;
        
        void SetVignetteColour(const Eegeo::v3& colour);
        void SetVignetteRadiusModifier(float radiusModifier);
        
        const Eegeo::v3& GetVignetteColour() const;
        float GetVignetteRadiusModifier() const;
        
    private:
        Eegeo::v3 m_colour;
        float m_radiusModifier;
    };
}

#endif /* defined(__ExampleApp__PostProcessVignetteRenderable__) */
