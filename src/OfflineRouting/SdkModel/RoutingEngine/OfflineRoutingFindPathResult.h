// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "OfflineRoutingPointOnGraph.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                struct OfflineRoutingFindPathResult
                {
                    OfflineRoutingFindPathResult()
                    : m_pathFound(false)
                    , m_distance(0)
                    {}

                    OfflineRoutingFindPathResult(bool pathFound,
                                                 const OfflineRoutingPointOnGraph& startPoint,
                                                 const OfflineRoutingPointOnGraph& endPoint,
                                                 const std::vector<OfflineRoutingGraphNodeId>& pathNodes,
                                                 double distance)
                    : m_pathFound(pathFound)
                    , m_startPoint(startPoint)
                    , m_endPoint(endPoint)
                    , m_pathNodes(pathNodes)
                    , m_distance(distance)
                    {}

                    bool GetPathFound() const { return m_pathFound; }
                    const OfflineRoutingPointOnGraph& GetStartPoint() const { return m_startPoint; }
                    const OfflineRoutingPointOnGraph& GetEndPoint() const { return m_endPoint; }
                    const std::vector<OfflineRoutingGraphNodeId>& GetPathNodes() const { return m_pathNodes; }
                    double GetPathDistance() const { return m_distance; }

                private:
                    bool m_pathFound;
                    OfflineRoutingPointOnGraph m_startPoint;
                    OfflineRoutingPointOnGraph m_endPoint;
                    std::vector<OfflineRoutingGraphNodeId> m_pathNodes;
                    double m_distance;
                };
            }
        }
    }
}
