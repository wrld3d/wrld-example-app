// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IOfflineRoutingPathFinder.h"
#include "OfflineRoutingPointOnGraph.h"
#include "VectorMath.h"
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
                    OfflineRoutingPathFinder(IOfflineRoutingDataRepository& offlineRoutingDataRepository);
                    ~OfflineRoutingPathFinder();

                    OfflineRoutingFindPathResult FindPath(const OfflineRoutingPointOnGraph& startPoint, const OfflineRoutingPointOnGraph& goalPoint) override;

                    //micropather graph implementation
                    float LeastCostEstimate( void* stateStart, void* stateEnd ) override;
                    void AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent ) override;
                    void PrintStateInfo( void* state ) override;


                private:
                    void OnGraphBuilt(const OfflineRoutingGraphBuildResults& graphBuildResults);

                    void CreatePathFinder(size_t size, size_t avgAdjacentNodes);
                    const Eegeo::dv3& GetPointFromState(void* state);
                    OfflineRoutingGraphNodeId GetIdFromState(void* state);
                    const std::vector<OfflineRoutingGraphNodeId>& GetAdjacentNodes(void* state);

                    IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;

                    Eegeo::Helpers::TCallback1<OfflineRoutingPathFinder, const OfflineRoutingGraphBuildResults&> m_graphBuiltCallback;

                    micropather::MicroPather* m_pPather;
                    OfflineRoutingPointOnGraph m_startPoint;
                    OfflineRoutingPointOnGraph m_goalPoint;
                };
            }
        }
    }
}
