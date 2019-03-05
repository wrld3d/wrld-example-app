// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingMicroPatherGraph.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingPointOnGraph.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingHelpers.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
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

                void OfflineRoutingMicroPatherGraph::SetTransportationMode(const Eegeo::Routes::Webservice::TransportationMode& transportationMode)
                {
                    m_transportationMode = transportationMode;
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
                    return Helpers::Distance(GetPointFromState(stateStart), GetPointFromState(stateEnd)) / Helpers::GetSpeedForTransportationMode(m_transportationMode);
                }

                void OfflineRoutingMicroPatherGraph::AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent )
                {
                    float durationMultiplier = 1;
                    const auto& currentNodeId = GetIdFromState(state);

                    if (currentNodeId != PATHER_START_END_POINT_NODE_ID)
                    {
                        const auto& currentNode = m_offlineRoutingDataRepository.GetGraphNode(currentNodeId);
                        const auto& currentFeature = m_offlineRoutingDataRepository.GetFeature(currentNode.GetFeatureId());
                        if (currentFeature.GetDurationMultiplier() > 0)
                        {
                            durationMultiplier = currentFeature.GetDurationMultiplier();
                        }
                    }

                    const auto& adjacentNodes = GetAdjacentNodes(state);
                    const auto& statePoint = GetPointFromState(state);

                    for (const auto& nodeId : adjacentNodes)
                    {
                        const auto* node = &m_offlineRoutingDataRepository.GetGraphNode(nodeId);

                        float duration = Helpers::Distance(statePoint, node->GetPoint()) / Helpers::GetSpeedForTransportationMode(m_transportationMode);
                        float adjNodeEdgeCost = duration * durationMultiplier;
                        micropather::StateCost stateCost = {const_cast<void*>(static_cast<const void*>(node)), adjNodeEdgeCost};
                        adjacent->push_back(stateCost);
                    }

                    const auto stateNodeId = GetIdFromState(state);

                    if (stateNodeId != PATHER_START_END_POINT_NODE_ID)
                    {
                        const auto& goalNodeEdges = m_goalPoint.GetLinkedEdges();
                        if(std::find(goalNodeEdges.begin(), goalNodeEdges.end(), stateNodeId) != goalNodeEdges.end())
                        {
                            //This node can be linked to the final node
                            micropather::StateCost stateCost = {&m_goalPoint, Helpers::Distance(statePoint, m_goalPoint.GetPoint())};
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
