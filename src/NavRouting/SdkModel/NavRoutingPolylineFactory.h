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
                float miterLimit = 17.5f;
                double routeElevation = 0;
                Eegeo::Positioning::ElevationMode::Type routeElevationMode = Eegeo::Positioning::ElevationMode::Type::HeightAboveGround;
                bool shouldScaleWithMap = false;
            };
            
            class NavRoutingPolylineFactory : public INavRoutingPolylineFactory, private Eegeo::NonCopyable
            {
            public:
                NavRoutingPolylineFactory(PolyLineArgs::IShapeService& shapeService,
                                          const NavRoutingPolylineConfig& polylineConfig);
                
                RouteLines CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                        const Eegeo::v4& color) override;
                
                RouteLines CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                        const Eegeo::v4& forwardColor,
                                                        const Eegeo::v4& backwardColor,
                                                        int splitIndex,
                                                        const Eegeo::Space::LatLong& closestPointOnRoute) override;
                
                RouteLines CreateLinesForFloorTransition(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                         const std::string& indoorMapId,
                                                         int floorBefore,
                                                         int floorAfter,
                                                         const Eegeo::v4& color) override;
                
            private:
                PolyLineArgs::IShapeService& m_shapeService;
                
                float m_routeThickness;
                float m_miterLimit;
                double m_routeElevation;
                Eegeo::Positioning::ElevationMode::Type m_routeElevationMode;
                bool m_shouldScaleWithMap;
                
                PolyLineArgs::ShapeModel::IdType MakeVerticalLine(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                  const std::string& indoorMapId,
                                                                  int floor,
                                                                  double heightStart,
                                                                  double heightEnd,
                                                                  const Eegeo::v4& color);
                
                PolyLineArgs::ShapeModel::IdType CreatePolyline(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                const Eegeo::v4& color,
                                                                bool isIndoors = false,
                                                                const std::string& indoorMapId = "",
                                                                int indoorMapFloorId = 0,
                                                                bool hasPerPointElevation = false,
                                                                const std::vector<double>& perPointElevations = std::vector<double>());
            };
        }
    }
}
