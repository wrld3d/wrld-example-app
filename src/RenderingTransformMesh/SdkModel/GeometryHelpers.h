// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "AllVertexTypes.h"
#include "Types.h"
#include "VectorMath.h"


namespace ExampleApp
{
    namespace RenderingTransformMesh
    {
        namespace SdkModel
        {
            namespace GeometryHelpers
            {
                void BuildQuadCW(const Eegeo::v2& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
                
                void BuildQuadCCW(const Eegeo::v2& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
                
                void BuildBoxCW(const Eegeo::v3& halfDimensions, std::vector<Eegeo::Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
            }
        }
    }
}