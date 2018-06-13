// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "NavRouting.h"
#include "NavRoutingDirectionModel.h"

#include <vector>
#include <unordered_map>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRouteDrawingController
            {
            public:

                virtual ~INavRouteDrawingController() {}
                
                virtual void DrawRoute(const Eegeo::v4& color) = 0;

                virtual void ClearRoute() = 0;
                
                virtual void SetRouteStepColor(int step, const Eegeo::v4& color) = 0;

                virtual void UpdateRouteStepProgress(int step,
                                                     const Eegeo::v4& colorForCrossedPath,
                                                     const Eegeo::v4& colorForUpcomingPath,
                                                     int splitIndex,
                                                     const Eegeo::Space::LatLong& closestPointOnRoute) = 0;
            };
        }
    }
}
