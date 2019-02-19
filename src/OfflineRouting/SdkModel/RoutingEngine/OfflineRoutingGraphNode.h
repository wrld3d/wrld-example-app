// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "VectorMath.h"
#include "InteriorId.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                struct OfflineRoutingGraphNode
                {
                    OfflineRoutingGraphNodeId id;
                    Eegeo::dv3 point;
                    std::vector<OfflineRoutingGraphNodeId> nodeEdges;
                    int floorId;
                    OfflineRoutingFeatureId featureId;
                    Eegeo::Resources::Interiors::InteriorId indoorId;

                    OfflineRoutingGraphNode()
                    : id(0)
                    , point(Eegeo::dv3::Zero())
                    , floorId(0)
                    , featureId(0)
                    {}

                    OfflineRoutingGraphNode(const OfflineRoutingGraphNodeId nodeId,
                                            const Eegeo::dv3& ecefPoint,
                                            const std::vector<OfflineRoutingGraphNodeId>& graphNodeEdges,
                                            const int nodeFloorId,
                                            const OfflineRoutingFeatureId routingFeatureId,
                                            const Eegeo::Resources::Interiors::InteriorId& nodeIndoorId)
                    : id(nodeId)
                    , point(ecefPoint)
                    , nodeEdges(graphNodeEdges)
                    , floorId(nodeFloorId)
                    , featureId(routingFeatureId)
                    , indoorId(nodeIndoorId)
                    {}
                };
            }
        }
    }
}
