// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TexturedClipSpaceVertexLayout.h"
#include "TexturedClipSpaceVertex.h"
#include "VertexLayout.h"
#include "Graphics.h"

namespace Examples
{
    Eegeo::Rendering::VertexLayouts::VertexLayout* CreateTexturedClipSpaceLayout()
    {
        typedef Eegeo::Rendering::VertexLayouts::VertexLayout VertexLayout;
        typedef Eegeo::Rendering::VertexLayouts::VertexLayoutElement VertexLayoutElement;
        
        VertexLayout* pLayout = Eegeo_NEW(VertexLayout)(sizeof(TexturedClipSpaceVertex));
        
        ptrdiff_t positionOffset = offsetof(TexturedClipSpaceVertex, m_x);
        pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 2, GL_FLOAT, positionOffset));
        
        ptrdiff_t uvOffset = offsetof(TexturedClipSpaceVertex, m_u);
        pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
        
        return pLayout;
    }
}