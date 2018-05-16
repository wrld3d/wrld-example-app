// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRouteDrawingController.h"
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
            class NavRouteDrawingController : public INavRouteDrawingController, private Eegeo::NonCopyable
            {
            public:
                NavRouteDrawingController(PolyLineArgs::IShapeService& shapeService);

                ~NavRouteDrawingController() override;
                
                void AddRoute(const std::vector<NavRoutingDirectionModel>& directions,
                              const Eegeo::v4& color) override;
                
                void ClearRoute() override;
                
                void SetRouteColor(int routeStep, const Eegeo::v4& color) override;
                
            private:
                PolyLineArgs::IShapeService& m_shapeService;
                std::unordered_map<int, std::vector<PolyLineArgs::ShapeModel::IdType>> m_routes;

                float m_routeThickness;
                float m_miterLimit;
                double m_routeElevation;
                Eegeo::Positioning::ElevationMode::Type m_routeElevationMode;
                bool m_shouldScaleWithMap;

                void AddLineForRouteDirection(int routeStep,
                                              const NavRoutingDirectionModel& directionModel,
                                              const Eegeo::v4& color);

                void AddLinesForFloorTransition(int routeStep,
                                                const NavRoutingDirectionModel& currentDirection,
                                                const NavRoutingDirectionModel& directionBefore,
                                                const NavRoutingDirectionModel& directionAfter,
                                                const Eegeo::v4& color);

                PolyLineArgs::ShapeModel::IdType MakeVerticalLine(const NavRoutingDirectionModel& currentDirection,
                                                                  int floor,
                                                                  double height,
                                                                  const Eegeo::v4& color);
            };
        }
    }
}
