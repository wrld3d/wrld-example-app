// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingPathFinder.h"
#include "OfflineRoutingFindPathResult.h"
#include "IOfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingGraphBuildResults.h"
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
                    const bool SHOULD_CACHE_GRAPH_WEIGHTS = false;
                }

                OfflineRoutingPathFinder::OfflineRoutingPathFinder(IOfflineRoutingDataRepository& offlineRoutingDataRepository)
                : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
                , m_pPather(nullptr)
                , m_graphBuiltCallback(this, &OfflineRoutingPathFinder::OnGraphBuilt)
                {
                    m_pMicroPatherGraph = Eegeo_NEW(OfflineRoutingMicroPatherGraph)(offlineRoutingDataRepository);

                    m_offlineRoutingDataRepository.RegisterGraphBuiltCallback(m_graphBuiltCallback);
                }

                OfflineRoutingPathFinder::~OfflineRoutingPathFinder()
                {
                    m_offlineRoutingDataRepository.UnregisterGraphBuiltCallback(m_graphBuiltCallback);

                    Eegeo_DELETE m_pPather;
                    Eegeo_DELETE m_pMicroPatherGraph;
                }

                void OfflineRoutingPathFinder::CreatePathFinder(size_t size, size_t avgAdjacentNodes)
                {
                    if (size == 0)
                    {
                        return;
                    }

                    Eegeo_DELETE m_pPather;

                    auto stateSize = size <= STATE_ALLOCATION_RATIO ? size : size / STATE_ALLOCATION_RATIO;
                    m_pPather = Eegeo_NEW(micropather::MicroPather)(m_pMicroPatherGraph,
                                                                    static_cast<unsigned int>(stateSize),
                                                                    static_cast<unsigned int>(avgAdjacentNodes),
                                                                    SHOULD_CACHE_GRAPH_WEIGHTS);
                }

                OfflineRoutingFindPathResult OfflineRoutingPathFinder::FindPath(const OfflineRoutingPointOnGraph& startPoint,
                                                                                const OfflineRoutingPointOnGraph& goalPoint,
                                                                                const Eegeo::Routes::Webservice::TransportationMode& transportationMode)
                {
                    if (m_pPather == nullptr)
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

                    m_pMicroPatherGraph->SetStartPoint(startPoint);
                    m_pMicroPatherGraph->SetEndPoint(goalPoint);
                    m_pMicroPatherGraph->SetTransportationMode(transportationMode);

                    micropather::MPVector< void* > path;
                    float totalCost = 0;
                    auto* pStartPoint = &m_pMicroPatherGraph->GetStartPoint();
                    auto* pEndPoint = &m_pMicroPatherGraph->GetEndPoint();
                    int result = m_pPather->Solve( const_cast<void*>(static_cast<const void*>(pStartPoint)),
                                                   const_cast<void*>(static_cast<const void*>(pEndPoint)),
                                                   &path,
                                                   &totalCost);

                    if (result != micropather::MicroPather::SOLVED)
                    {
                        return OfflineRoutingFindPathResult();
                    }

                    std::vector<OfflineRoutingGraphNodeId> pathNodes;
                    pathNodes.reserve(path.size());

                    for (int i = 0; i < path.size(); i++)
                    {
                        const auto id = m_pMicroPatherGraph->GetIdFromState(path[i]);
                        if (id != PATHER_START_END_POINT_NODE_ID)
                        {
                            pathNodes.emplace_back(id);
                        }
                    }

                    m_pPather->Reset();
                    return OfflineRoutingFindPathResult(true,
                                                        m_pMicroPatherGraph->GetStartPoint(),
                                                        m_pMicroPatherGraph->GetEndPoint(),
                                                        pathNodes,
                                                        totalCost);
                }

                void OfflineRoutingPathFinder::OnGraphBuilt(const OfflineRoutingGraphBuildResults& graphBuildResults)
                {
                    CreatePathFinder(graphBuildResults.GetGraphSize(), graphBuildResults.GetAverageEdges());
                }
            }
        }
    }
}
