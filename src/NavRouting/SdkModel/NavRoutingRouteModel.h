// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include "NavRoutingDirectionModel.h"
#include "RouteData.h"

#include <vector>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingRouteModel
            {
            public:
                NavRoutingRouteModel();

                NavRoutingRouteModel(const double duration,
                                     const double distance,
                                     const std::vector<NavRoutingDirectionModel>& directions,
                                     const Eegeo::Routes::Webservice::RouteData& sourceRouteData);

                const double GetDuration() const;
                const double GetDistance() const;
                const std::vector<NavRoutingDirectionModel>& GetDirections() const;
                const Eegeo::Routes::Webservice::RouteData& GetSourceRouteData() const;

                void UpdateDirection(int index, const NavRoutingDirectionModel& directionModel);

            private:

                double m_duration;
                double m_distance;
                std::vector<NavRoutingDirectionModel> m_directions;
                Eegeo::Routes::Webservice::RouteData m_sourceRoute;
            };
        }
    }
}
