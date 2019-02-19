// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingGraphNode.h"

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
                        Eegeo::Space::LatLongAltitude point(coordinate.GetLatitude(), coordinate.GetLongitude(), floorId * FloorHeight);
                        std::vector<OfflineRoutingGraphNodeId> edges;
                        auto nodeId = NextGraphNodeId();

                        if (i > 0)
                        {
                            auto& previousNode = graphNodes.at(i-1);
                            previousNode.nodeEdges.push_back(nodeId);
                            edges.push_back(previousNode.id);
                        }

                        graphNodes.emplace_back(nodeId, point.ToECEF(), edges, floorId, featureId, indoorId);
                    }


                    return graphNodes;
                }

                OfflineRoutingFeature OfflineRoutingDataBuilder::BuildFeature(const std::string& type,
                                                                              const std::string& name,
                                                                              int floorId,
                                                                              const Eegeo::Resources::Interiors::InteriorId& indoorId)
                {
                    return OfflineRoutingFeature(NextFeatureId(), type, name, floorId, indoorId);
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
