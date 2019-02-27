// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"
#include "LatLongAltitude.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class IOfflineRoutingGraphPositioner
                {
                public:
                    virtual ~IOfflineRoutingGraphPositioner() {}

                    virtual OfflineRoutingPointOnGraph FindPointOnGraph(const Eegeo::Space::LatLong& point,
                                                                        const int floorId,
                                                                        const double maxDistance) = 0;
                };
            }
        }
    }
}
