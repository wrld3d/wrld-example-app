// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"

#include <unordered_map>

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
                    OfflineRoutingDataRepository();
                    ~OfflineRoutingDataRepository() {}

                    void AddGraphNode(const OfflineRoutingGraphNode& node) override;
                    void AddFeature(const OfflineRoutingFeature& feature) override;

                    bool HasGraphNode(const OfflineRoutingGraphNodeId& id) const override;
                    bool HasFeature(const OfflineRoutingFeatureId& id) const override;

                    const OfflineRoutingGraphNode& GetGraphNode(const OfflineRoutingGraphNodeId& id) const override;
                    const OfflineRoutingFeature& GetFeature(const OfflineRoutingFeatureId& id) const override;

                private:

                    typedef std::unordered_map<OfflineRoutingFeatureId, OfflineRoutingFeature> OfflineRoutingFeatures;
                    typedef std::unordered_map<OfflineRoutingGraphNodeId, OfflineRoutingGraphNode> OfflineRoutingGraphNodes;

                    OfflineRoutingFeatures m_interiorFeatures;
                    OfflineRoutingGraphNodes m_interiorGraphNodes;
                };
            }
        }
    }
}
