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
                
                virtual void AddRoute(const std::vector<NavRoutingDirectionModel>& directions,
                              const Eegeo::v4& color) = 0;

                virtual void ClearRoute() = 0;

                virtual void SetRouteColor(int routeStep, const Eegeo::v4& color) = 0;
            };
        }
    }
}
