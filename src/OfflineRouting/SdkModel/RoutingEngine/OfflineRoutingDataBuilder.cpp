// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingGraphNode.h"
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
                    const int FloorHeight = 10;

                    OfflineRoutingGraphNode GetGraphNode(const OfflineRoutingGraphNodeId nodeId,
                                                         const Eegeo::Space::LatLong& coordinate,
                                                         const int floorId,
                                                         const size_t iteratorPos,
                                                         const OfflineRoutingFeatureId& featureId,
                                                         const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                         std::vector<OfflineRoutingGraphNode>& graphNodes)
                    {
                        Eegeo::Space::LatLongAltitude point(coordinate.GetLatitude(), coordinate.GetLongitude(), floorId * FloorHeight);
                        std::vector<OfflineRoutingGraphNodeId> edges;

                        if (iteratorPos > 0)
                        {
                            auto& previousNode = graphNodes.at(iteratorPos-1);
                            previousNode.AddNodeEdge(nodeId);
                            edges.push_back(previousNode.GetId());
                        }

                        return OfflineRoutingGraphNode(nodeId, point.ToECEF(), edges, floorId, featureId, indoorId);
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

                        graphNodes.emplace_back(GetGraphNode(NextGraphNodeId(),
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
                                                                                                          const Eegeo::Resources::Interiors::InteriorId& indoorId)
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
                                                             i,
                                                             featureId,
                                                             indoorId,
                                                             graphNodes));
                    }

                    return graphNodes;
                }

                OfflineRoutingFeature OfflineRoutingDataBuilder::BuildFeature(const std::string& type,
                                                                              const std::string& name,
                                                                              const Eegeo::Resources::Interiors::InteriorId& indoorId)
                {
                    return OfflineRoutingFeature(NextFeatureId(), type, name, indoorId);
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
