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
                struct OfflineRoutingPointOnGraph
                {
                    OfflineRoutingPointOnGraph()
                    : m_pointValid(false)
                    , m_point(Eegeo::dv3::Zero())
                    , m_floorId(0)
                    , m_featureId(0)
                    , m_isPositionedOnNode(false)
                    {}

                    OfflineRoutingPointOnGraph(const bool pointValid,
                                               const Eegeo::dv3& point,
                                               const std::vector<OfflineRoutingGraphNodeId>& nodeEdges,
                                               const int floorId,
                                               const OfflineRoutingFeatureId featureId,
                                               const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                               const bool isPositionedOnNode)
                    : m_pointValid(pointValid)
                    , m_point(point)
                    , m_nodeEdges(nodeEdges)
                    , m_floorId(floorId)
                    , m_featureId(featureId)
                    , m_indoorId(indoorId)
                    , m_isPositionedOnNode(isPositionedOnNode)
                    {}

                    bool GetIsPointValid() const { return m_pointValid; }
                    const Eegeo::dv3& GetPoint() const { return m_point; }
                    const std::vector<OfflineRoutingGraphNodeId>& GetLinkedEdges() const { return m_nodeEdges; }
                    int GetFloorId() const { return m_floorId; }
                    OfflineRoutingFeatureId GetFeatureId() const { return m_featureId; }
                    const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return m_indoorId; }
                    bool GetIsPositionedOnNode() const { return m_isPositionedOnNode; }

                private:
                    bool m_pointValid;
                    Eegeo::dv3 m_point;
                    std::vector<OfflineRoutingGraphNodeId> m_nodeEdges;
                    int m_floorId;
                    OfflineRoutingFeatureId m_featureId;
                    Eegeo::Resources::Interiors::InteriorId m_indoorId;
                    bool m_isPositionedOnNode;
                };
            }
        }
    }
}
