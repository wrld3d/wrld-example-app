// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IOfflineRoutingPathFinder.h"
#include "OfflineRoutingPointOnGraph.h"
#include "VectorMath.h"
#include "Types.h"

#include "micropather.h"
#include "OfflineRoutingMicroPatherGraph.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class OfflineRoutingPathFinder : public IOfflineRoutingPathFinder, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingPathFinder(IOfflineRoutingDataRepository& offlineRoutingDataRepository);
                    ~OfflineRoutingPathFinder();

                    OfflineRoutingFindPathResult FindPath(const OfflineRoutingPointOnGraph& startPoint, const OfflineRoutingPointOnGraph& goalPoint) override;

                private:
                    void OnGraphBuilt(const OfflineRoutingGraphBuildResults& graphBuildResults);

                    void CreatePathFinder(size_t size, size_t avgAdjacentNodes);

                    IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;

                    Eegeo::Helpers::TCallback1<OfflineRoutingPathFinder, const OfflineRoutingGraphBuildResults&> m_graphBuiltCallback;

                    micropather::MicroPather* m_pPather;
                    OfflineRoutingMicroPatherGraph* m_pMicroPatherGraph;
                };
            }
        }
    }
}
