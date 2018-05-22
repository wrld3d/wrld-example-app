// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "NavRouting.h"
#include "NavRoutingDirectionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingPolylineFactory
            {
            public:
                
                virtual ~INavRoutingPolylineFactory() {}
                
                virtual RouteLines CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                const Eegeo::v4& color) = 0;
                
                virtual RouteLines CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                const Eegeo::v4& forwardColor,
                                                                const Eegeo::v4& backwardColor,
                                                                int splitIndex,
                                                                const Eegeo::Space::LatLong& closestPointOnRoute) = 0;
                
                virtual RouteLines CreateLinesForFloorTransition(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                 const std::string& indoorMapId,
                                                                 int floorBefore,
                                                                 int floorAfter,
                                                                 const Eegeo::v4& color) = 0;
            };
        }
    }
}
