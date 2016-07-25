// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GeometryHelpers.h"
#include "Bounds.h"

namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            namespace GeometryHelpers
            {
                void BuildQuadCW(const Eegeo::v2& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
                {
                    Eegeo::v3 points[4] =
                    {
                        Eegeo::v3(halfDimensions.x, 0, -halfDimensions.y),
                        Eegeo::v3(halfDimensions.x, 0, halfDimensions.y),
                        Eegeo::v3(-halfDimensions.x, 0, halfDimensions.y),
                        Eegeo::v3(-halfDimensions.x, 0, -halfDimensions.y),
                        
                    };
                    
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[0], Eegeo::v2(1, 1)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[1], Eegeo::v2(1, 0)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[2], Eegeo::v2(0, 0)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[3], Eegeo::v2(0, 1)));
                    
                    out_triangleIndices.push_back(0);
                    out_triangleIndices.push_back(3);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(3);
                    out_triangleIndices.push_back(2);
                }
                
                void BuildQuadCCW(const Eegeo::v2& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
                {
                    Eegeo::v3 points[4] =
                    {
                        Eegeo::v3(halfDimensions.x, 0, -halfDimensions.y),
                        Eegeo::v3(halfDimensions.x, 0, halfDimensions.y),
                        Eegeo::v3(-halfDimensions.x, 0, halfDimensions.y),
                        Eegeo::v3(-halfDimensions.x, 0, -halfDimensions.y),
                        
                    };
                    
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[0], Eegeo::v2(1, 1)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[1], Eegeo::v2(1, 0)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[2], Eegeo::v2(0, 0)));
                    out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[3], Eegeo::v2(0, 1)));
                    
                    out_triangleIndices.push_back(0);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(3);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(2);
                    out_triangleIndices.push_back(3);
                }
                
                void BuildBoxCW(const Eegeo::v3& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
                {
                    const int faces = 6;
                    const int pointsPerFace = 4;
                    out_vertices.clear();
                    out_triangleIndices.clear();
                    out_vertices.reserve(pointsPerFace*faces);
                    out_triangleIndices.reserve(faces*3*2);
                    
                    Eegeo::v3 points[8] =
                    {
                        Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z),
                        Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                        Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                        Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                        Eegeo::v3(-halfDimensions.x, halfDimensions.y, halfDimensions.z),
                        Eegeo::v3(-halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                        Eegeo::v3(-halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                        Eegeo::v3(-halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                    };
                    
                    int pointIndices[faces*pointsPerFace] =
                    {
                        1, 0, 3, 2,
                        0, 4, 2, 6,
                        4, 5, 6, 7,
                        5, 1, 7, 3,
                        4, 0, 5, 1,
                        7, 3, 6, 2,
                    };
                    
                    
                    Eegeo::Geometry::Bounds2D uvRects[] =
                    {
                        Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.0f), Eegeo::v2(0.5f, 0.5f)),    // +ve x, "0"
                        Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.0f), Eegeo::v2(1.0f, 0.5f)),    // +ve z, "1"
                        Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.5f), Eegeo::v2(0.5f, 1.0f)),    // -ve x, "2"
                        Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.5f), Eegeo::v2(1.0f, 1.0f)),    // -ve z, "3"
                        Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // +ve y (top)
                        Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // -ve y (bottom)
                    };
                    
                    
                    for (int i = 0; i < 6; ++i)
                    {
                        
                        const Eegeo::Geometry::Bounds2D& uvRect = uvRects[i];
                        
                        u16 offset = static_cast<u16>(i*pointsPerFace);
                        out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[pointIndices[offset + 0]], Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                        out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[pointIndices[offset + 1]], Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                        out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[pointIndices[offset + 2]], Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                        out_vertices.push_back(Eegeo::Rendering::VertexTypes::CreateTexturedVertex(points[pointIndices[offset + 3]], Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                        
                        out_triangleIndices.push_back(offset + 0);
                        out_triangleIndices.push_back(offset + 1);
                        out_triangleIndices.push_back(offset + 2);
                        out_triangleIndices.push_back(offset + 2);
                        out_triangleIndices.push_back(offset + 1);
                        out_triangleIndices.push_back(offset + 3);
                    }
                }
            }
        }
    }
}