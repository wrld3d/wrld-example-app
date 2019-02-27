// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingMicroPatherGraph.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingPointOnGraph.h"
#include "OfflineRoutingGraphNode.h"

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
                    float Distance(const Eegeo::dv3& a, const Eegeo::dv3& b)
                    {
                        return Eegeo::Math::Sqrtf(static_cast<float>(a.SquareDistanceTo(b)));
                    }
                }

                OfflineRoutingMicroPatherGraph::OfflineRoutingMicroPatherGraph(IOfflineRoutingDataRepository& offlineRoutingDataRepository)
                : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
                {}

                OfflineRoutingMicroPatherGraph::~OfflineRoutingMicroPatherGraph()
                {}

                void OfflineRoutingMicroPatherGraph::SetStartPoint(const OfflineRoutingPointOnGraph& startPoint)
                {
                    m_startPoint = startPoint;
                }
                void OfflineRoutingMicroPatherGraph::SetEndPoint(const OfflineRoutingPointOnGraph& goalPoint)
                {
                    m_goalPoint = goalPoint;
                }

                const OfflineRoutingPointOnGraph& OfflineRoutingMicroPatherGraph::GetStartPoint()
                {
                    return m_startPoint;
                }

                const OfflineRoutingPointOnGraph& OfflineRoutingMicroPatherGraph::GetEndPoint()
                {
                    return m_goalPoint;
                }

                //micropather graph implementation
                float OfflineRoutingMicroPatherGraph::LeastCostEstimate( void* stateStart, void* stateEnd )
                {
                    return Distance(GetPointFromState(stateStart), GetPointFromState(stateEnd));
                }

                void OfflineRoutingMicroPatherGraph::AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent )
                {
                    const auto& adjacentNodes = GetAdjacentNodes(state);
                    const auto& statePoint = GetPointFromState(state);

                    for (const auto& nodeId : adjacentNodes)
                    {
                        const auto* node = &m_offlineRoutingDataRepository.GetGraphNode(nodeId);

                        micropather::StateCost stateCost = {const_cast<void*>(static_cast<const void*>(node)),
                                                            Distance(statePoint, node->GetPoint())};
                        adjacent->push_back(stateCost);
                    }

                    const auto stateNodeId = GetIdFromState(state);

                    if (stateNodeId != PATHER_START_END_POINT_NODE_ID)
                    {
                        const auto& goalNodeEdges = m_goalPoint.GetLinkedEdges();
                        if(std::find(goalNodeEdges.begin(), goalNodeEdges.end(), stateNodeId) != goalNodeEdges.end())
                        {
                            //This node can be linked to the final node
                            micropather::StateCost stateCost = {&m_goalPoint, Distance(statePoint, m_goalPoint.GetPoint())};
                            adjacent->push_back(stateCost);
                        }
                    }
                }

                void OfflineRoutingMicroPatherGraph::PrintStateInfo( void* state ){}

                const Eegeo::dv3& OfflineRoutingMicroPatherGraph::GetPointFromState(const void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        const OfflineRoutingPointOnGraph* node = static_cast<const OfflineRoutingPointOnGraph*>(state);
                        return node->GetPoint();
                    }

                    const OfflineRoutingGraphNode* node = static_cast<const OfflineRoutingGraphNode*>(state);
                    return node->GetPoint();
                }

                OfflineRoutingGraphNodeId OfflineRoutingMicroPatherGraph::GetIdFromState(const void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        return PATHER_START_END_POINT_NODE_ID;
                    }

                    const OfflineRoutingGraphNode* node = static_cast<const OfflineRoutingGraphNode*>(state);
                    return node->GetId();
                }

                const std::vector<OfflineRoutingGraphNodeId>& OfflineRoutingMicroPatherGraph::GetAdjacentNodes(const void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        const OfflineRoutingPointOnGraph* node = static_cast<const OfflineRoutingPointOnGraph*>(state);
                        return node->GetLinkedEdges();
                    }

                    const OfflineRoutingGraphNode* node = static_cast<const OfflineRoutingGraphNode*>(state);
                    return node->GetEdges();
                }
            }
        }
    }
}
