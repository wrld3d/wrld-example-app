// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TexturedClipSpaceMeshFactory.h"

namespace Examples
{
    TexturedClipSpaceMeshFactory::TexturedClipSpaceMeshFactory(Eegeo::Rendering::GlBufferPool& glBufferPool,
                                                               const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout,
                                                               const size_t vertexSize)
    : Eegeo::Rendering::MeshFactories::MeshFactory(glBufferPool, vertexLayout, vertexSize)
    {
    }
}
