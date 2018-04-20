// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include <map>
#include "VectorMath.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                class ColorChangeBatchOperation
                {
                public:
                    static std::vector<ColorChangeBatchOperation *> BuildBatchOperations(
                                    const std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>& renderables,
                                    const std::map<std::string, Eegeo::v4>& highlightLookup);
                    
                    const std::string& GetInteriorId() { return m_interiorId; }
                    const Eegeo::v4& GetHighlightColor() { return m_color; }
                    const std::vector<std::string>& GetEntityIds() { return m_entityIds; }
                private:
                    
                    ColorChangeBatchOperation(const std::string& interiorId, const Eegeo::v4& color);
                    void AddEntityToOperation(const std::string& newEntityInOpertaion);
                    
                    const std::string& m_interiorId;
                    const Eegeo::v4& m_color;
                    std::vector<std::string> m_entityIds;
                };
            }
        }
    }
}
