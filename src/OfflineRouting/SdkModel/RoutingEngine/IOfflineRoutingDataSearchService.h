// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "VectorMath.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class IOfflineRoutingDataSearchService
                {
                public:
                    virtual ~IOfflineRoutingDataSearchService() {}

                    virtual std::vector<OfflineRoutingGraphNodeId> FindNodesWithinDistance(const Eegeo::dv3& point, double distance) = 0;
                    virtual OfflineRoutingGraphNodeId FindNearestNode(const Eegeo::dv3& point) = 0;
                };
            }
        }
    }
}
