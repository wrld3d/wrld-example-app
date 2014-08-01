// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__TexturedClipSpaceMeshFactory__
#define __ExampleApp__TexturedClipSpaceMeshFactory__

#include "MeshFactory.h"
#include "Rendering.h"

namespace Examples
{
    class TexturedClipSpaceMeshFactory : public Eegeo::Rendering::MeshFactories::MeshFactory
    {
    public:
        TexturedClipSpaceMeshFactory(Eegeo::Rendering::GlBufferPool& glBufferPool,
                                     const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout,
                                     const size_t vertexSize);
    };
}

#endif /* defined(__ExampleApp__TexturedClipSpaceMeshFactory__) */
