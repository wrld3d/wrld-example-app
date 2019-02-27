// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataSearchService.h"
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
                    struct KDTreeAdapter
                    {
                        struct Node
                        {
                            OfflineRoutingGraphNodeId id;
                            Eegeo::dv3 point;
                        };

                        void BuildNodes(const std::unordered_map<OfflineRoutingGraphNodeId, OfflineRoutingGraphNode>& graphNodes)
                        {
                            m_nodes.clear();
                            m_nodes.reserve(graphNodes.size());

                            for (const auto& it : graphNodes)
                            {
                                const OfflineRoutingGraphNode& node = it.second;
                                Node kdTreeNode;
                                kdTreeNode.id = node.GetId();
                                kdTreeNode.point = node.GetPoint();

                                m_nodes.push_back(kdTreeNode);
                            }
                        }

                        const Node& GetNode(const size_t index) const
                        {
                            return m_nodes.at(index);
                        }

                        // nanoflann adapter implementation
                        inline size_t kdtree_get_point_count() const { return m_nodes.size(); }

                        inline double kdtree_get_pt(const size_t index, const size_t dim) const
                        {
                            const auto& node = GetNode(index);

                            switch (dim)
                            {
                                case 0:
                                    return node.point.x;
                                case 1:
                                    return node.point.y;
                                default:
                                    return node.point.z;
                            }
                        }

                        template <class BBOX>
                        bool kdtree_get_bbox(BBOX& /* bb */) const { return false; }

                    private:
                        std::vector<Node>  m_nodes;
                    };
                }

                OfflineRoutingDataSearchService::OfflineRoutingDataSearchService()
                {
                    m_pKDTreeAdapter = Eegeo_NEW(KDTreeAdapter)();
                    m_pSearchServiceKDTree = Eegeo_NEW(SearchServiceKDTree)(KDTREE_DIMENSIONS,
                                                                            *m_pKDTreeAdapter,
                                                                            nanoflann::KDTreeSingleIndexAdaptorParams());
                }

                OfflineRoutingDataSearchService::~OfflineRoutingDataSearchService()
                {
                    Eegeo_DELETE m_pSearchServiceKDTree;
                    Eegeo_DELETE m_pKDTreeAdapter;
                }

                void OfflineRoutingDataSearchService::BuildSearchTree(const std::unordered_map<OfflineRoutingGraphNodeId, OfflineRoutingGraphNode>& graphNodes)
                {
                    m_pKDTreeAdapter->BuildNodes(graphNodes);
                    m_pSearchServiceKDTree->buildIndex();
                }

                std::vector<OfflineRoutingGraphNodeId> OfflineRoutingDataSearchService::FindNodesWithinDistance(const Eegeo::dv3& point, double distance)
                {
                    std::vector<std::pair<size_t, double>> retMatches;

                    nanoflann::SearchParams params;
                    const double queryPoint[3] = { point.x, point.y, point.z};
                    const size_t nMatches = m_pSearchServiceKDTree->radiusSearch(&queryPoint[0], distance, retMatches, params);

                    std::vector<OfflineRoutingGraphNodeId> nodes;
                    nodes.reserve(nMatches);

                    for (size_t i = 0; i < nMatches; i++)
                    {
                        const auto& treeNode = m_pKDTreeAdapter->GetNode(retMatches[i].first);
                        nodes.push_back(treeNode.id);
                    }

                    return nodes;
                }

                OfflineRoutingGraphNodeId OfflineRoutingDataSearchService::FindNearestNode(const Eegeo::dv3& point)
                {
                    size_t numResults = 1;
                    size_t retIndex;
                    double outDistanceSqr;
                    const double queryPoint[3] = { point.x, point.y, point.z};

                    numResults = m_pSearchServiceKDTree->knnSearch(&queryPoint[0], numResults, &retIndex, &outDistanceSqr);

                    if (numResults > 0)
                    {
                        return m_pKDTreeAdapter->GetNode(retIndex).id;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
    }
}
