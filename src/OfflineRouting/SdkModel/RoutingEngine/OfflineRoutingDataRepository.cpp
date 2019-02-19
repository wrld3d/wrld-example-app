// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "InteriorId.h"
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
                    const double MinimumDistance = 0.00001;
                }

                OfflineRoutingDataRepository::OfflineRoutingDataRepository()
                {}

                void OfflineRoutingDataRepository::AddGraphNode(const OfflineRoutingGraphNode& node)
                {
                    Eegeo_ASSERT(!(HasGraphNode(node.GetId())), "Already have data for node %d", node.GetId());

                    m_interiorGraphNodes[node.GetId()] = node;

                    VerifyNodeEdges(node.GetId());
                }

                void OfflineRoutingDataRepository::AddGraphNodes(const std::vector<OfflineRoutingGraphNode>& nodes)
                {
                    for (const auto& node: nodes)
                    {
                        AddGraphNode(node);
                    }
                }

                void OfflineRoutingDataRepository::AddFeature(const OfflineRoutingFeature& feature)
                {
                    Eegeo_ASSERT(!(HasFeature(feature.GetId())), "Already have data for feature %d", feature.GetId());

                    m_interiorFeatures[feature.GetId()] = feature;
                }

                bool OfflineRoutingDataRepository::HasGraphNode(const OfflineRoutingGraphNodeId& id) const
                {
                    return m_interiorGraphNodes.find(id) != m_interiorGraphNodes.end();
                }

                bool OfflineRoutingDataRepository::HasFeature(const OfflineRoutingFeatureId& id) const
                {
                    return m_interiorFeatures.find(id) != m_interiorFeatures.end();
                }

                const OfflineRoutingGraphNode& OfflineRoutingDataRepository::GetGraphNode(const OfflineRoutingGraphNodeId& id) const
                {
                    Eegeo_ASSERT((HasGraphNode(id)), "Does not have data for node %d", id);
                    return m_interiorGraphNodes.at(id);
                }

                const OfflineRoutingFeature& OfflineRoutingDataRepository::GetFeature(const OfflineRoutingFeatureId& id) const
                {
                    Eegeo_ASSERT((HasFeature(id)), "Does not have data for feature %d", id);
                    return m_interiorFeatures.at(id);
                }

                std::vector<OfflineRoutingGraphNodeId> OfflineRoutingDataRepository::FindNodesAtDistance(Eegeo::dv3 point, double distance)
                {
                    std::vector<OfflineRoutingGraphNodeId> nodesWithinDistance;
                    for (auto& it : m_interiorGraphNodes)
                    {
                        auto& node = it.second;

                        if (point.SquareDistanceTo(node.GetPoint()) < distance)
                        {
                            nodesWithinDistance.push_back(node.GetId());
                        }
                    }

                    return nodesWithinDistance;
                }

                void OfflineRoutingDataRepository::VerifyNodeEdges(OfflineRoutingGraphNodeId nodeId)
                {
                    auto& node = m_interiorGraphNodes.at(nodeId);

                    auto connectedNodesIds = FindNodesAtDistance(node.GetPoint(), MinimumDistance);

                    for (auto connectedNodesId : connectedNodesIds)
                    {
                        if (connectedNodesId == nodeId)
                        {
                            continue;
                        }

                        auto& connectedNode = m_interiorGraphNodes.at(connectedNodesId);
                        node.AddNodeEdge(connectedNodesId);
                        connectedNode.AddNodeEdge(nodeId);
                    }
                }
            }
        }
    }
}
