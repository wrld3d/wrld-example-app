// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeatureBuilder.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingHelpers.h"
#include "Types.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                namespace
                {
                    OfflineRoutingGraphNode GetGraphNode(const OfflineRoutingGraphNodeId nodeId,
                                                         const Eegeo::Space::LatLong& coordinate,
                                                         const int floorId,
                                                         const OfflineRoutingFeatureId& featureId,
                                                         const Eegeo::Resources::Interiors::InteriorId& indoorId)
                    {
                        std::vector<OfflineRoutingGraphNodeId> edges;
                        auto point = Helpers::GetEcefPointFromLatlong(coordinate, floorId);
                        return OfflineRoutingGraphNode(nodeId, point, edges, floorId, featureId, indoorId);
                    }

                    OfflineRoutingGraphNode GetGraphNodeWithLinkedEdges(const OfflineRoutingGraphNodeId nodeId,
                                                                        const Eegeo::Space::LatLong& coordinate,
                                                                        const int floorId,
                                                                        const size_t iteratorPos,
                                                                        const OfflineRoutingFeatureId& featureId,
                                                                        const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                        std::vector<OfflineRoutingGraphNode>& graphNodes)
                    {
                        std::vector<OfflineRoutingGraphNodeId> edges;

                        if (iteratorPos > 0)
                        {
                            auto& previousNode = graphNodes.at(iteratorPos-1);
                            previousNode.AddNodeEdge(nodeId);
                            edges.push_back(previousNode.GetId());
                        }

                        auto point = Helpers::GetEcefPointFromLatlong(coordinate, floorId);
                        return OfflineRoutingGraphNode(nodeId, point, edges, floorId, featureId, indoorId);
                    }
                }

                OfflineRoutingDataBuilder::OfflineRoutingDataBuilder()
                : m_featureId(1)
                , m_graphNodeId(1)
                {}

                std::vector<OfflineRoutingGraphNode> OfflineRoutingDataBuilder::BuildGraphNodes(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                                int floorId,
                                                                                                const OfflineRoutingFeatureId& featureId,
                                                                                                const Eegeo::Resources::Interiors::InteriorId& indoorId)
                {
                    const auto nodeCount = coordinates.size();

                    std::vector<OfflineRoutingGraphNode> graphNodes;
                    graphNodes.reserve(nodeCount);

                    for (std::vector<OfflineRoutingGraphNode>::size_type i = 0; i < nodeCount; i++)
                    {
                        const auto& coordinate = coordinates.at(i);

                        graphNodes.emplace_back(GetGraphNodeWithLinkedEdges(NextGraphNodeId(),
                                                                            coordinate,
                                                                            floorId,
                                                                            i,
                                                                            featureId,
                                                                            indoorId,
                                                                            graphNodes));
                    }

                    return graphNodes;
                }

                std::vector<OfflineRoutingGraphNode> OfflineRoutingDataBuilder::BuildMultiFloorGraphNodes(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                                          std::vector<int> floorIds,
                                                                                                          const OfflineRoutingFeatureId& featureId,
                                                                                                          const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                                          bool isOneWay)
                {
                    Eegeo_ASSERT(coordinates.size() == floorIds.size(), "Invalid multi floor data. Floor count does not match coordinate count");

                    auto size = coordinates.size();

                    std::vector<OfflineRoutingGraphNode> graphNodes;
                    graphNodes.reserve(size);

                    for (size_t i = 0; i < size; ++i)
                    {
                        const auto& coordinate = coordinates.at(i);
                        const auto floorId = floorIds.at(i);

                        graphNodes.emplace_back(GetGraphNode(NextGraphNodeId(),
                                                             coordinate,
                                                             floorId,
                                                             featureId,
                                                             indoorId));
                    }

                    for (size_t i = 0; i < size; ++i)
                    {
                        auto& node = graphNodes.at(i);

                        auto startIt = isOneWay ? i + 1 : 0;

                        for (size_t j = startIt; j < size; j++)
                        {
                            if (i == j)
                            {
                                continue;
                            }

                            auto& linkedNode = graphNodes.at(j);
                            node.AddNodeEdge(linkedNode.GetId());

                            if (!isOneWay)
                            {
                                linkedNode.AddNodeEdge(node.GetId());
                            }
                        }
                    }

                    return graphNodes;
                }

                OfflineRoutingFeatureBuilder OfflineRoutingDataBuilder::GetFeatureBuilder(const std::string& type,
                                                                                          const std::string& name,
                                                                                          const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                                          bool isMultiFloor,
                                                                                          bool isOneWay,
                                                                                          int durationMultiplier)
                {
                    return OfflineRoutingFeatureBuilder(NextFeatureId(), type, name, indoorId, isMultiFloor, isOneWay, durationMultiplier);
                }

                OfflineRoutingFeatureId OfflineRoutingDataBuilder::NextFeatureId()
                {
                    return m_featureId++;
                }

                OfflineRoutingGraphNodeId OfflineRoutingDataBuilder::NextGraphNodeId()
                {
                    return m_graphNodeId++;
                }
            }
        }
    }
}
