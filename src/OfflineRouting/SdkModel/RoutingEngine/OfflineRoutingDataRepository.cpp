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
                OfflineRoutingDataRepository::OfflineRoutingDataRepository(OfflineRoutingDataSearchService& dataSearchService)
                : m_dataSearchService(dataSearchService)
                {}

                void OfflineRoutingDataRepository::AddGraphNode(const OfflineRoutingGraphNode& node)
                {
                    Eegeo_ASSERT(!(HasGraphNode(node.GetId())), "Already have data for node %d", node.GetId());

                    m_interiorGraphNodes[node.GetId()] = node;
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

                const OfflineRoutingGraphNodes& OfflineRoutingDataRepository::GetGraph() const
                {
                    return m_interiorGraphNodes;
                }

                const OfflineRoutingFeatures& OfflineRoutingDataRepository::GetFeatures() const
                {
                    return m_interiorFeatures;
                }

                void OfflineRoutingDataRepository::JoinNodesWithinMinimumDistance(OfflineRoutingGraphNodeId nodeId)
                {
                    /* At this point we probably have multiple disjointed graphs for each line strings
                     * We want to find all the nodes are essentially at the same place and create
                     * connections between them so that they can become a single cohesive graph that
                     * can be used to find paths.
                     */
                    auto& node = m_interiorGraphNodes.at(nodeId);

                    auto connectedNodesIds = m_dataSearchService.FindNodesWithinDistance(node.GetPoint(), MinimumDistanceInMeters);

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

                void OfflineRoutingDataRepository::BuildGraph()
                {
                    m_dataSearchService.BuildSearchTree(m_interiorGraphNodes);

                    size_t totalEdges = 0;

                    for (auto &it : m_interiorGraphNodes)
                    {
                        JoinNodesWithinMinimumDistance(it.first);
                        totalEdges += it.second.GetEdges().size();
                    }

                    const auto size = m_interiorGraphNodes.size();
                    auto results = OfflineRoutingGraphBuildResults(size, totalEdges / size);
                    m_graphBuiltCallbacks.ExecuteCallbacks(results);
                }

                void OfflineRoutingDataRepository::RegisterGraphBuiltCallback(OfflineRoutingDataRepositoryBuildCompletedCallback& callback)
                {
                    m_graphBuiltCallbacks.AddCallback(callback);
                }

                void OfflineRoutingDataRepository::UnregisterGraphBuiltCallback(OfflineRoutingDataRepositoryBuildCompletedCallback& callback)
                {
                    m_graphBuiltCallbacks.RemoveCallback(callback);
                }
            }
        }
    }
}
