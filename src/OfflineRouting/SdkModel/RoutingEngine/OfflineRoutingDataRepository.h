// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingDataSearchService.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class OfflineRoutingDataRepository : public IOfflineRoutingDataRepository, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingDataRepository(OfflineRoutingDataSearchService& dataSearchService);
                    ~OfflineRoutingDataRepository() {}

                    void AddGraphNode(const OfflineRoutingGraphNode& node) override;
                    void AddGraphNodes(const std::vector<OfflineRoutingGraphNode>& nodes) override;
                    void AddFeature(const OfflineRoutingFeature& feature) override;

                    bool HasGraphNode(const OfflineRoutingGraphNodeId& id) const override;
                    bool HasFeature(const OfflineRoutingFeatureId& id) const override;

                    const OfflineRoutingGraphNode& GetGraphNode(const OfflineRoutingGraphNodeId& id) const override;
                    const OfflineRoutingFeature& GetFeature(const OfflineRoutingFeatureId& id) const override;

                    const OfflineRoutingGraphNodes& GetGraph() const override;
                    const OfflineRoutingFeatures& GetFeatures() const override;

                    OfflineRoutingGraphBuildResults BuildGraph() override;

                private:
                    void JoinNodesWithinMinimumDistance(OfflineRoutingGraphNodeId nodeId);

                    OfflineRoutingFeatures m_interiorFeatures;
                    OfflineRoutingGraphNodes m_interiorGraphNodes;

                    OfflineRoutingDataSearchService& m_dataSearchService;
                };
            }
        }
    }
}
