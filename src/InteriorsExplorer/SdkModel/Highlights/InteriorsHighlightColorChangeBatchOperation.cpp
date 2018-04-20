// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsHighlightColorChangeBatchOperation.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorId.h"
#include <unordered_map>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                namespace
                {
                    const Eegeo::v4 transparentHighlightColor(1.0f, 1.0f, 1.0f, 0.0f);
                }
                
                ColorChangeBatchOperation::ColorChangeBatchOperation(const std::string& interiorId, const Eegeo::v4& color)
                : m_interiorId(interiorId)
                , m_color(color)
                {
                }
                
                std::vector<ColorChangeBatchOperation *> ColorChangeBatchOperation::BuildBatchOperations(
                    const std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>& renderables,
                    const std::map<std::string, Eegeo::v4>& highlightLookup)
                {
                    std::vector<ColorChangeBatchOperation *> operations;
                    
                    for (const auto& pHighlightRenderable : renderables)
                    {
                        const std::string& renderableId = pHighlightRenderable->GetRenderableId();

                        const auto highlightColorMapIter = highlightLookup.find(renderableId);
                        const Eegeo::v4& highlightColor = (highlightColorMapIter != highlightLookup.end()) ?
                            highlightColorMapIter->second :
                            transparentHighlightColor;

                        //m_interiorsHighlightService.SetHighlight(, pHighlightRenderable->GetHighlightId(), highlightColor);
                        const auto& interiorId = pHighlightRenderable->GetInteriorId();
                        const auto buildingIdIter = std::find_if(operations.begin(), operations.end(), [&interiorId, &highlightColor](const ColorChangeBatchOperation* c) {
                            return
                            c->m_interiorId == interiorId &&
                            c->m_color == highlightColor; });
                        if(buildingIdIter == operations.end())
                        {
                            const auto& operation = new ColorChangeBatchOperation(pHighlightRenderable->GetInteriorId(), highlightColor);
                            operation->AddEntityToOperation(pHighlightRenderable->GetHighlightId());
                            operations.push_back(operation);
                        }
                        else{
                            (*buildingIdIter)->AddEntityToOperation(pHighlightRenderable->GetHighlightId());
                        }
                    }
                    
                    return operations;
                }
                
                void ColorChangeBatchOperation::AddEntityToOperation(const std::string & entityId)
                {
                    m_entityIds.push_back(entityId);
                }
            }
        }
    }
}
