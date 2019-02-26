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
                class IOfflineRoutingPathFinder
                {
                public:
                    virtual ~IOfflineRoutingPathFinder() {}

                    virtual void CreatePathFinderFromGraph(size_t size, size_t avgAdjacentNodes) = 0;

                    virtual OfflineRoutingFindPathResult FindPath(const OfflineRoutingPointOnGraph& startPoint, const OfflineRoutingPointOnGraph& goalPoint) = 0;
                };
            }
        }
    }
}
