// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "VectorMath.h"
#include "InteriorId.h"

#include <vector>
#include <algorithm>

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

                    const OfflineRoutingGraphNodeId GetId() const { return id; }
                    const Eegeo::dv3 GetPoint() const { return point; }
                    const std::vector<OfflineRoutingGraphNodeId>& GetEdges() const { return nodeEdges; }
                    const int GetFloorId() const { return floorId; }
                    const OfflineRoutingFeatureId GetFeatureId() const { return featureId; }
                    const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return indoorId; }

                    void AddNodeEdge(const OfflineRoutingGraphNodeId edgeId)
                    {
                        if(std::find(nodeEdges.begin(), nodeEdges.end(), edgeId) == nodeEdges.end())
                        {
                            nodeEdges.push_back(edgeId);
                        }
                    }

                private:
                    OfflineRoutingGraphNodeId id;
                    Eegeo::dv3 point;
                    std::vector<OfflineRoutingGraphNodeId> nodeEdges;
                    int floorId;
                    OfflineRoutingFeatureId featureId;
                    Eegeo::Resources::Interiors::InteriorId indoorId;
                };
            }
        }
    }
}
