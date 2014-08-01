// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PostProcessVignetteRenderable.h"

namespace Examples
{
    void PostProcessVignetteRenderable::Render(Eegeo::Rendering::GLState& glState) const
    {
        m_material->SetStatePerRenderable(this, glState);
        
        m_pMesh->BindVertexBuffers(GetVertexBinding(), glState);
        
        const u32 indexCount = m_pMesh->GetNumOfIndices();
        
        Eegeo_ASSERT(indexCount != 0);
        
        Eegeo_GL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (void*)(0)));
        
        m_pMesh->UnbindVertexBuffers(glState);
    }
    
    void PostProcessVignetteRenderable::SetVignetteColour(const Eegeo::v3& colour)
    {
        m_colour = colour;
    }
    
    void PostProcessVignetteRenderable::SetVignetteRadiusModifier(float radiusModifier)
    {
        Eegeo_ASSERT(radiusModifier > 0.f);
        m_radiusModifier = radiusModifier;
    }
    
    const Eegeo::v3& PostProcessVignetteRenderable::GetVignetteColour() const
    {
        return m_colour;
    }
    
    float PostProcessVignetteRenderable::GetVignetteRadiusModifier() const
    {
        return m_radiusModifier;
    }
}
