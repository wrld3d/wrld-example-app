// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "GLBufferPool.h"
#include "Mesh.h"
#include "Types.h"
#include "VertexLayoutPool.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            
            class TexturedVertexMeshFactory : Eegeo::NonCopyable
            {
            private:
                Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
                Eegeo::Rendering::GlBufferPool& m_glBufferPool;
                unsigned int m_id;
                
            public:
                TexturedVertexMeshFactory(Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool, Eegeo::Rendering::GlBufferPool& glBufferPool);
                
                Eegeo::Rendering::Mesh* CreateQuadCWMesh(float width, float height);
                Eegeo::Rendering::Mesh* CreateQuadCWMesh(float width, float height, std::string debugName);
                
                Eegeo::Rendering::Mesh* CreateQuadCCWMesh(float width, float height);
                Eegeo::Rendering::Mesh* CreateQuadCCWMesh(float width, float height, std::string debugName);
                
                Eegeo::Rendering::Mesh* CreateMesh(std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> meshVertices, std::vector<u16> triangleIndices);
                Eegeo::Rendering::Mesh* CreateMesh(std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> meshVertices, std::vector<u16> triangleIndices, std::string debugName);
            };
            
        }
    }
}