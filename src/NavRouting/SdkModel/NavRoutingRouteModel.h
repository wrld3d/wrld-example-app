// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include "NavRoutingDirectionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingRouteModel
            {
            public:
                NavRoutingRouteModel(const double duration,
                                     const double distance,
                                     const std::vector<NavRoutingDirectionModel>& directions);

                const double GetDuration() const;
                const double GetDistance() const;
                const std::vector<NavRoutingDirectionModel>& GetDirections() const;

            private:

                double m_duration;
                double m_distance;
                std::vector<NavRoutingDirectionModel> m_directions;
            };
        }
    }
}
