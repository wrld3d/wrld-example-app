// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
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
                class OfflineRoutingMicroPatherGraph : public micropather::Graph, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingMicroPatherGraph(IOfflineRoutingDataRepository& offlineRoutingDataRepository);
                    ~OfflineRoutingMicroPatherGraph();

                    void SetStartPoint(const OfflineRoutingPointOnGraph& startPoint);
                    void SetEndPoint(const OfflineRoutingPointOnGraph& goalPoint);

                    const OfflineRoutingPointOnGraph& GetStartPoint();
                    const OfflineRoutingPointOnGraph& GetEndPoint();

                    OfflineRoutingGraphNodeId GetIdFromState(const void* state);

                    //micropather graph implementation
                    float LeastCostEstimate( void* stateStart, void* stateEnd ) override;
                    void AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent ) override;
                    void PrintStateInfo( void* state ) override;

                private:
                    const Eegeo::dv3& GetPointFromState(const void* state);
                    const std::vector<OfflineRoutingGraphNodeId>& GetAdjacentNodes(const void* state);

                    IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;

                    OfflineRoutingPointOnGraph m_startPoint;
                    OfflineRoutingPointOnGraph m_goalPoint;
                };
            }
        }
    }
}
