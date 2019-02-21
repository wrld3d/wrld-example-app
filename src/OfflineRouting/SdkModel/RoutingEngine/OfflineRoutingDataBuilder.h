// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"
#include "LatLongAltitude.h"
#include "IOfflineRoutingDataBuilder.h"

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
                class OfflineRoutingDataBuilder : public IOfflineRoutingDataBuilder, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingDataBuilder();
                    ~OfflineRoutingDataBuilder() {}

                    std::vector<OfflineRoutingGraphNode> BuildGraphNodes(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                         int floorId,
                                                                         const OfflineRoutingFeatureId& featureId,
                                                                         const Eegeo::Resources::Interiors::InteriorId& indoorId) override;

                    std::vector<OfflineRoutingGraphNode> BuildMultiFloorGraphNodes(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                   std::vector<int> floorIds,
                                                                                   const OfflineRoutingFeatureId& featureId,
                                                                                   const Eegeo::Resources::Interiors::InteriorId& indoorId) override;

                    OfflineRoutingFeature BuildFeature(const std::string& type,
                                                       const std::string& name,
                                                       const Eegeo::Resources::Interiors::InteriorId& indoorId) override;

                private:
                    OfflineRoutingFeatureId NextFeatureId();
                    OfflineRoutingGraphNodeId NextGraphNodeId();

                    OfflineRoutingFeatureId m_featureId;
                    OfflineRoutingGraphNodeId m_graphNodeId;
                };
            }
        }
    }
}