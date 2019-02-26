// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IOfflineRoutingPathFinder.h"
#include "OfflineRoutingPointOnGraph.h"
#include "Types.h"

#include "micropather.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class OfflineRoutingPathFinder : public IOfflineRoutingPathFinder, public micropather::Graph, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingPathFinder(const IOfflineRoutingDataRepository& offlineRoutingDataRepository);
                    ~OfflineRoutingPathFinder();

                    void CreatePathFinderFromGraph(size_t size, size_t avgAdjacentNodes) override;

                    OfflineRoutingFindPathResult FindPath(const OfflineRoutingPointOnGraph& startPoint, const OfflineRoutingPointOnGraph& goalPoint) override;

                    const Eegeo::dv3& GetPointFromState(void* state);
                    OfflineRoutingGraphNodeId GetIdFromState(void* state);
                    const std::vector<OfflineRoutingGraphNodeId>& GetAdjacentNodes(void* state);

                    //micropather graph implementation
                    float LeastCostEstimate( void* stateStart, void* stateEnd ) override;
                    void AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent ) override;
                    void PrintStateInfo( void* state ) override;


                private:
                    const IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;

                    micropather::MicroPather* m_pPather;
                    OfflineRoutingPointOnGraph m_startPoint;
                    OfflineRoutingPointOnGraph m_goalPoint;
                };
            }
        }
    }
}
