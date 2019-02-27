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
                    OfflineRoutingGraphNode()
                    : m_id(0)
                    , m_point(Eegeo::dv3::Zero())
                    , m_floorId(0)
                    , m_featureId(0)
                    {}

                    OfflineRoutingGraphNode(const OfflineRoutingGraphNodeId nodeId,
                                            const Eegeo::dv3& ecefPoint,
                                            const std::vector<OfflineRoutingGraphNodeId>& graphNodeEdges,
                                            const int nodeFloorId,
                                            const OfflineRoutingFeatureId routingFeatureId,
                                            const Eegeo::Resources::Interiors::InteriorId& nodeIndoorId)
                    : m_id(nodeId)
                    , m_point(ecefPoint)
                    , m_nodeEdges(graphNodeEdges)
                    , m_floorId(nodeFloorId)
                    , m_featureId(routingFeatureId)
                    , m_indoorId(nodeIndoorId)
                    {}

                    const OfflineRoutingGraphNodeId GetId() const { return m_id; }
                    const Eegeo::dv3& GetPoint() const { return m_point; }
                    const std::vector<OfflineRoutingGraphNodeId>& GetEdges() const { return m_nodeEdges; }
                    const int GetFloorId() const { return m_floorId; }
                    const OfflineRoutingFeatureId GetFeatureId() const { return m_featureId; }
                    const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return m_indoorId; }

                    void AddNodeEdge(const OfflineRoutingGraphNodeId edgeId)
                    {
                        Eegeo_ASSERT(edgeId != GetId(), "OfflineRoutingGraphNode cannot add itself as edge.");

                        if(std::find(m_nodeEdges.begin(), m_nodeEdges.end(), edgeId) == m_nodeEdges.end())
                        {
                            m_nodeEdges.push_back(edgeId);
                        }
                    }

                private:
                    OfflineRoutingGraphNodeId m_id;
                    Eegeo::dv3 m_point;
                    std::vector<OfflineRoutingGraphNodeId> m_nodeEdges;
                    int m_floorId;
                    OfflineRoutingFeatureId m_featureId;
                    Eegeo::Resources::Interiors::InteriorId m_indoorId;
                };
            }
        }
    }
}
