// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingController.h"
#include "PolylineShapeBuilder.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRouteDrawingController::NavRouteDrawingController(PolyLineArgs::IShapeService& shapeService)
            : m_shapeService(shapeService)
            {

            }

            NavRouteDrawingController::~NavRouteDrawingController()
            {
                ClearRoute();
            }

            void NavRouteDrawingController::AddRoute(const std::vector<NavRoutingDirectionModel>& directions,
                                                     const Eegeo::v4& color)
            {
                for (int i = 0; i < directions.size(); ++i)
                {
                    const NavRoutingDirectionModel& directionModel = directions[i];

                    if (directionModel.GetPath().size() < 2)
                    {
                        continue;
                    }

                    if (directionModel.GetIsMultiFloor())
                    {
                        bool isValidTransition = i > 0 && i < (directions.size() - 1) && directionModel.GetIsIndoors();

                        if (!isValidTransition)
                        {
                            continue;
                        }

                        const NavRoutingDirectionModel& directionBefore = directions[i-1];
                        const NavRoutingDirectionModel& directionAfter = directions[i+1];

                        AddLinesForFloorTransition(i, directionModel, directionBefore, directionAfter, color);
                    }
                    else
                    {
                        AddLineForRouteDirection(i, directionModel, color);
                    }
                }
            }

            void NavRouteDrawingController::ClearRoute()
            {
                for(const auto& routeIt : m_routes)
                {
                    for (const auto& shapeId : routeIt.second)
                    {
                        m_shapeService.Destroy(shapeId);
                    }
                }

                m_routes.clear();
            }

            void NavRouteDrawingController::SetRouteColor(int routeStep, const Eegeo::v4& color)
            {
                if (m_routes.find(routeStep)!=m_routes.end())
                {
                    for (const auto& shapeId : m_routes[routeStep])
                    {
                        PolyLineArgs::ShapeModel &shapeModel = m_shapeService.Get(shapeId);
                        shapeModel.SetFillColor(color);
                    }
                }
            }

            void NavRouteDrawingController::AddLineForRouteDirection(int routeStep,
                                                                     const NavRoutingDirectionModel& directionModel,
                                                                     const Eegeo::v4& color)
            {
                PolyLineArgs::ShapeModel::IdType shapeId;
                if (directionModel.GetIsIndoors())
                {
                    const auto& params = Eegeo::Shapes::Polylines::PolylineShapeBuilder()
                                        .SetCoordinates(directionModel.GetPath())
                                        .SetFillColor(color)
                                        .SetThickness(10.0f)//TODO
                                        .SetMiterLimit(10.0f)
                                        .SetElevation(0)
                                        .SetElevationMode(Eegeo::Positioning::ElevationMode::Type::HeightAboveGround)
                                        .SetIndoorMap(directionModel.GetIndoorMapId().Value(), directionModel.GetIndoorMapFloorId())
                                        .SetShouldScaleWithMap(true)
                                        .Build();

                    shapeId = m_shapeService.Create(params);
                }
                else
                {
                    const auto& params = Eegeo::Shapes::Polylines::PolylineShapeBuilder()
                                        .SetCoordinates(directionModel.GetPath())
                                        .SetFillColor(color)
                                        .SetThickness(10.0f)//TODO
                                        .SetMiterLimit(10.0f)
                                        .SetElevation(0)
                                        .SetElevationMode(Eegeo::Positioning::ElevationMode::Type::HeightAboveGround)
                                        .SetShouldScaleWithMap(true)
                                        .Build();

                    shapeId = m_shapeService.Create(params);
                }

                std::vector<PolyLineArgs::ShapeModel::IdType> polyLines;
                polyLines.push_back(shapeId);
                m_routes[routeStep] = polyLines;
            }

            void NavRouteDrawingController::AddLinesForFloorTransition(int routeStep,
                                                                       const NavRoutingDirectionModel& currentDirection,
                                                                       const NavRoutingDirectionModel& directionBefore,
                                                                       const NavRoutingDirectionModel& directionAfter,
                                                                       const Eegeo::v4& color)
            {
                int floorBefore = directionBefore.GetIndoorMapFloorId();
                int floorAfter = directionAfter.GetIndoorMapFloorId();

                double verticalLineHeight = 5.0;
                double lineHeight = (floorAfter > floorBefore) ? verticalLineHeight : -verticalLineHeight;

                std::vector<PolyLineArgs::ShapeModel::IdType> polyLines;
                polyLines.push_back(MakeVerticalLine(currentDirection, floorBefore, lineHeight, color));
                polyLines.push_back(MakeVerticalLine(currentDirection, floorAfter, -lineHeight, color));
                m_routes[routeStep] = polyLines;
            }

            PolyLineArgs::ShapeModel::IdType NavRouteDrawingController::MakeVerticalLine(const NavRoutingDirectionModel& currentDirection,
                                                                                         int floor,
                                                                                         double height,
                                                                                         const Eegeo::v4& color)
            {
                std::vector<double> perPointElevations;
                perPointElevations.push_back(0);
                perPointElevations.push_back(height);

                const auto& params = Eegeo::Shapes::Polylines::PolylineShapeBuilder()
                        .SetCoordinates(currentDirection.GetPath())
                        .SetFillColor(color)
                        .SetThickness(10.0f)//TODO
                        .SetMiterLimit(10.0f)
                        .SetElevation(0)
                        .SetElevationMode(Eegeo::Positioning::ElevationMode::Type::HeightAboveGround)
                        .SetIndoorMap(currentDirection.GetIndoorMapId().Value(), floor)
                        .SetShouldScaleWithMap(true)
                        .SetPerPointElevations(perPointElevations)
                        .Build();

                return m_shapeService.Create(params);
            }
        }
    }
}
