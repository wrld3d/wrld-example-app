// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingPathFinder.h"
#include "OfflineRoutingFindPathResult.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "VectorMath.h"
#include "MathFunc.h"

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
                    const int STATE_ALLOCATION_RATIO = 4;
                    const bool SHOULD_CACHE_GRAPH_WEIGHTS = true;

                    float Distance(const Eegeo::dv3& a, const Eegeo::dv3& b)
                    {
                        double distance = a.SquareDistanceTo(b);

                        if (distance < MinimumDistanceInMeters)
                        {
                            return 0;
                        }

                        return Eegeo::Math::Sqrtf(static_cast<float>(distance));
                    }
                }

                OfflineRoutingPathFinder::OfflineRoutingPathFinder(const IOfflineRoutingDataRepository& offlineRoutingDataRepository)
                : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
                , m_pPather(NULL)
                {}

                OfflineRoutingPathFinder::~OfflineRoutingPathFinder()
                {
                    if (m_pPather != NULL)
                    {
                        Eegeo_DELETE m_pPather;
                    }
                }

                void OfflineRoutingPathFinder::CreatePathFinderFromGraph(size_t size, size_t avgAdjacentNodes)
                {
                    if (size == 0)
                    {
                        return;
                    }

                    auto stateSize = size <= STATE_ALLOCATION_RATIO ? size : size / STATE_ALLOCATION_RATIO;
                    m_pPather = Eegeo_NEW(micropather::MicroPather)(this,
                                                                    static_cast<unsigned int>(stateSize),
                                                                    static_cast<unsigned int>(avgAdjacentNodes),
                                                                    SHOULD_CACHE_GRAPH_WEIGHTS);
                }

                OfflineRoutingFindPathResult OfflineRoutingPathFinder::FindPath(const OfflineRoutingPointOnGraph& startPoint, const OfflineRoutingPointOnGraph& goalPoint)
                {
                    if (m_pPather == NULL)
                    {
                        return OfflineRoutingFindPathResult();
                    }

                    if ((!startPoint.GetIsPointValid()) || (!goalPoint.GetIsPointValid()))
                    {
                        return OfflineRoutingFindPathResult();
                    }

                    if (startPoint.GetInteriorId() != goalPoint.GetInteriorId())
                    {
                        return OfflineRoutingFindPathResult();
                    }

                    m_startPoint = startPoint;
                    m_goalPoint = goalPoint;

                    micropather::MPVector< void* > path;
                    float totalCost = 0;
                    int result = m_pPather->Solve( &m_startPoint, &m_goalPoint, &path, &totalCost);

                    if (result != micropather::MicroPather::SOLVED)
                    {
                        return OfflineRoutingFindPathResult();
                    }

                    std::vector<OfflineRoutingGraphNodeId> pathNodes;
                    pathNodes.reserve(path.size());

                    for (int i = 0; i < path.size(); i++)
                    {
                        const auto id = GetIdFromState(path[i]);
                        if (id != 0)
                        {
                            pathNodes.emplace_back(id);
                        }
                    }

                    return OfflineRoutingFindPathResult(true,
                                                        m_startPoint,
                                                        m_goalPoint,
                                                        pathNodes,
                                                        totalCost);
                }

                const Eegeo::dv3& OfflineRoutingPathFinder::GetPointFromState(void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        const OfflineRoutingPointOnGraph* node = (OfflineRoutingPointOnGraph*) state;
                        return node->GetPoint();
                    }
                    else
                    {
                        const OfflineRoutingGraphNode* node = (OfflineRoutingGraphNode*) state;
                        return node->GetPoint();
                    }
                }

                OfflineRoutingGraphNodeId OfflineRoutingPathFinder::GetIdFromState(void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        return 0;
                    }
                    else
                    {
                        const OfflineRoutingGraphNode* node = (OfflineRoutingGraphNode*) state;
                        return node->GetId();
                    }
                }

                const std::vector<OfflineRoutingGraphNodeId>& OfflineRoutingPathFinder::GetAdjacentNodes(void* state)
                {
                    if (state == (&m_startPoint) || state == (&m_goalPoint))
                    {
                        const OfflineRoutingPointOnGraph* node = (OfflineRoutingPointOnGraph*) state;
                        return node->GetLinkedEdges();
                    }
                    else
                    {
                        const OfflineRoutingGraphNode* node = (OfflineRoutingGraphNode*) state;
                        return node->GetEdges();
                    }
                }

                float OfflineRoutingPathFinder::LeastCostEstimate( void* stateStart, void* stateEnd )
                {
                    return Distance(GetPointFromState(stateStart), GetPointFromState(stateEnd));
                }

                void OfflineRoutingPathFinder::AdjacentCost( void* state, MP_VECTOR<micropather::StateCost> *adjacent )
                {
                    const auto& adjacentNodes = GetAdjacentNodes(state);
                    const auto& statePoint = GetPointFromState(state);

                    for (const auto& nodeId : adjacentNodes)
                    {
                        const auto& node = m_offlineRoutingDataRepository.GetGraphNode(nodeId);
                        micropather::StateCost stateCost = {(void*)&node, Distance(statePoint, node.GetPoint())};
                        adjacent->push_back(stateCost);
                    }

                    const auto stateNodeId = GetIdFromState(state);

                    if (stateNodeId != 0)
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

                void OfflineRoutingPathFinder::PrintStateInfo( void* state )
                {}
            }
        }
    }
}
