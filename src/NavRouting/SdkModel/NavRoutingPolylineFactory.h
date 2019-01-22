// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "NavRouting.h"
#include "INavRoutingPolylineFactory.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingPolylineConfig
            {
            public:
                float routeThickness = 17.5f;
                float miterLimit = 10.0f;
                double routeElevation = 0;
                Eegeo::Positioning::ElevationMode::Type routeElevationMode = Eegeo::Positioning::ElevationMode::Type::HeightAboveGround;
                bool shouldScaleWithMap = false;
            };
            
            class NavRoutingPolylineFactory : public INavRoutingPolylineFactory, private Eegeo::NonCopyable
            {
            public:
                NavRoutingPolylineFactory(PolyLineArgs::IShapeService& shapeService,
                                          const NavRoutingPolylineConfig& polylineConfig);

                std::vector<NavRoutingPolylineCreateParams> CreateLinesForRouteDirection(
                    const NavRoutingDirectionModel& directionModel,
                    const Eegeo::v4& color) override;

                std::vector<NavRoutingPolylineCreateParams> CreateLinesForRouteDirection(
                    const NavRoutingDirectionModel& directionModel,
                    const Eegeo::v4& forwardColor,
                    const Eegeo::v4& backwardColor,
                    int splitIndex,
                    const Eegeo::Space::LatLong& closestPointOnRoute) override;

                std::vector<NavRoutingPolylineCreateParams> CreateLinesForFloorTransition(
                    const std::vector<Eegeo::Space::LatLong>& coordinates,
                    const std::string& indoorMapId,
                    int floorBefore,
                    int floorAfter,
                    const Eegeo::v4& color) override;

                RoutePolylineIdVector CreatePolylines(const std::vector<NavRoutingPolylineCreateParams>& polylineCreateParams) override ;
                
            private:
                PolyLineArgs::IShapeService& m_shapeService;
                const NavRoutingPolylineConfig m_polylineConfig;

                RoutePolylineIdVector CreateAmalgamatedPolylinesForRange(
                    const std::vector<NavRoutingPolylineCreateParams>& polylineCreateParams,
                    const int rangeStartIndex,
                    const int rangeEndIndex
                );
            };
        }
    }
}
