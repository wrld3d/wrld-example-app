// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataSearchService.h"
#include "nanoflann.hpp"

#include <vector>
#include <unordered_map>

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
                    struct KDTreeAdapter;
                    const int KDTREE_DIMENSIONS = 3;
                }

                class OfflineRoutingDataSearchService : public IOfflineRoutingDataSearchService, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingDataSearchService();
                    ~OfflineRoutingDataSearchService();

                    void BuildSearchTree(const std::unordered_map<OfflineRoutingGraphNodeId, OfflineRoutingGraphNode>& graphNodes);

                    std::vector<OfflineRoutingGraphNodeId> FindNodesWithinDistance(const Eegeo::dv3& point, double distance) override;
                    OfflineRoutingGraphNodeId FindNearestNode(const Eegeo::dv3& point) override;

                private:
                    typedef nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<double, KDTreeAdapter> ,KDTreeAdapter, KDTREE_DIMENSIONS> SearchServiceKDTree;

                    KDTreeAdapter* m_pKDTreeAdapter;
                    SearchServiceKDTree* m_pSearchServiceKDTree;
                };
            }
        }
    }
}
