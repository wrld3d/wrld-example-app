// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "RouteData.h"

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

                    virtual OfflineRoutingFindPathResult FindPath(const OfflineRoutingPointOnGraph& startPoint,
                                                                  const OfflineRoutingPointOnGraph& goalPoint,
                                                                  const Eegeo::Routes::Webservice::TransportationMode& transportationMode) = 0;
                };
            }
        }
    }
}
