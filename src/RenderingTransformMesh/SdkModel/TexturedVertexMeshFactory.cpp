// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TexturedVertexMeshFactory.h"

#include <limits>
#include <cstdio>
#include "GeometryHelpers.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            namespace
            {
                std::string UnsignedToString(unsigned int i)
                {
                    char buffer[std::numeric_limits<unsigned int>::digits+1];
                    sprintf(buffer, "%d", i);
                    return std::string(buffer);
                }
            }
            
            TexturedVertexMeshFactory::TexturedVertexMeshFactory(Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool, Eegeo::Rendering::GlBufferPool& glBufferPool)
            : m_id(0)
            , m_vertexLayoutPool(vertexLayoutPool)
            , m_glBufferPool(glBufferPool)
            {
            }
            
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateQuadCWMesh(float width, float height)
            {
                return CreateQuadCWMesh(width, height, "UnnamedTexturedQuad"+UnsignedToString(m_id));
            }
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateQuadCWMesh(float width, float height, std::string debugName)
            {
                Eegeo::v2 halfDimensions(width/2, height/2);
                std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> quadVertices;
                std::vector<u16> triangleIndices;
                
                GeometryHelpers::BuildQuadCW(halfDimensions, quadVertices, triangleIndices);
                
                return CreateMesh(quadVertices, triangleIndices, debugName);
            }
            
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateQuadCCWMesh(float width, float height)
            {
                return CreateQuadCCWMesh(width, height, "UnnamedTexturedQuad"+UnsignedToString(m_id));
            }
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateQuadCCWMesh(float width, float height, std::string debugName)
            {
                Eegeo::v2 halfDimensions(width/2, height/2);
                std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> quadVertices;
                std::vector<u16> triangleIndices;
                
                GeometryHelpers::BuildQuadCCW(halfDimensions, quadVertices, triangleIndices);
                
                return CreateMesh(quadVertices, triangleIndices, debugName);
            }
            
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateMesh(std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> meshVertices, std::vector<u16> triangleIndices)
            {
                return CreateMesh(meshVertices, triangleIndices, "UnnamedTexturedMesh"+UnsignedToString(m_id));
            }
            Eegeo::Rendering::Mesh* TexturedVertexMeshFactory::CreateMesh(std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex> meshVertices, std::vector<u16> triangleIndices, std::string debugName)
            {
                size_t vertexBufferSizeBytes = sizeof(Eegeo::Rendering::VertexTypes::TexturedVertex) * meshVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                ++m_id;
                
                return Eegeo_NEW(Eegeo::Rendering::Mesh)(
                                                         m_vertexLayoutPool.GetForTexturedVertex(),
                                                         m_glBufferPool,
                                                         meshVertices.data(),
                                                         vertexBufferSizeBytes,
                                                         triangleIndices.data(),
                                                         indexBufferSizeBytes,
                                                         static_cast<u32>(triangleIndices.size()),
                                                         debugName
                                                         );
            }
        }
    }
}