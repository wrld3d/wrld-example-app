// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                struct OfflineRoutingGraphBuildResults
                {
                    OfflineRoutingGraphBuildResults()
                            : graphSize(0)
                            , averageEdges(0)
                    {}

                    OfflineRoutingGraphBuildResults(size_t size, size_t edges)
                            : graphSize(size)
                            , averageEdges(edges)
                    {}

                    const size_t graphSize;
                    const size_t averageEdges;
                };
            }
        }
    }
}
