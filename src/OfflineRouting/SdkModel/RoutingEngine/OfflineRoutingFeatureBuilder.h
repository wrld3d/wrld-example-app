// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "InteriorId.h"
#include "VectorMath.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class OfflineRoutingFeatureBuilder
                {
                public:
                    OfflineRoutingFeatureBuilder(const OfflineRoutingFeatureId featureId,
                                                 const std::string& featureType,
                                                 const std::string& featureName,
                                                 const Eegeo::Resources::Interiors::InteriorId& featureIndoorId,
                                                 bool isMultiFloor);

                    const OfflineRoutingFeatureId GetId() const;

                    OfflineRoutingFeatureBuilder& LinkNodes(const std::vector<OfflineRoutingGraphNode>& graphNodes);

                    OfflineRoutingFeature Build();

                private:
                    OfflineRoutingFeatureId m_id;
                    std::string m_type;
                    std::string m_name;
                    Eegeo::Resources::Interiors::InteriorId m_indoorId;
                    bool m_isMultiFloor;
                    std::vector<OfflineRoutingGraphNodeId> m_featureNodes;
                    std::vector<Eegeo::v3> m_featureSplinePoints;
                };
            }
        }
    }
}
