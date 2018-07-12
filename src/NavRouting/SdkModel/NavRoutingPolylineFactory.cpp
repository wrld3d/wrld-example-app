// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingPolylineFactory.h"
#include "PolylineShapeBuilder.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace
            {
                bool IsEqual(const Eegeo::Space::LatLong& first, const Eegeo::Space::LatLong& second)
                {
                    return first.ToECEF().SquareDistanceTo(second.ToECEF()) <= 0.00000000001;
                }
            }
            
            NavRoutingPolylineFactory::NavRoutingPolylineFactory(PolyLineArgs::IShapeService& shapeService,
                                                                 const NavRoutingPolylineConfig& polylineConfig)
            : m_shapeService(shapeService)
            , m_routeThickness(polylineConfig.routeThickness)
            , m_miterLimit(polylineConfig.miterLimit)
            , m_routeElevation(polylineConfig.routeElevation)
            , m_routeElevationMode(polylineConfig.routeElevationMode)
            , m_shouldScaleWithMap(polylineConfig.shouldScaleWithMap)
            {
                
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                               const Eegeo::v4& color)
            {
                RouteLines routeLines;
                const auto& coordinates = directionModel.GetPath();

                std::vector<Eegeo::Space::LatLong> uniqueCoordinates;
                uniqueCoordinates.reserve(coordinates.size());
                std::unique_copy (coordinates.begin(), coordinates.end(), std::back_inserter(uniqueCoordinates), IsEqual);

                if(uniqueCoordinates.size()>1)
                {
                    routeLines.push_back(CreatePolyline(uniqueCoordinates,
                                                        color,
                                                        directionModel.GetIsIndoors(),
                                                        directionModel.GetIndoorMapId().Value(),
                                                        directionModel.GetIndoorMapFloorId()));
                }
                
                return routeLines;
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                               const Eegeo::v4& forwardColor,
                                                                               const Eegeo::v4& backwardColor,
                                                                               int splitIndex,
                                                                               const Eegeo::Space::LatLong& closestPointOnRoute)
            {
                const auto& coordinates = directionModel.GetPath();
                std::size_t coordinatesSize = coordinates.size();
                bool hasReachedEnd = splitIndex == (coordinatesSize-1);
                
                if (hasReachedEnd)
                {
                    return CreateLinesForRouteDirection(directionModel,
                                                        backwardColor);
                }
                else
                {
                    RouteLines routeLines;
                    std::vector<Eegeo::Space::LatLong> backwardPath;
                    std::vector<Eegeo::Space::LatLong> forwardPath;
                    
                    auto forwardPathSize = coordinatesSize - (splitIndex + 1);
                    forwardPath.reserve(forwardPathSize + 1); //Extra space for the split point
                    
                    auto backwardPathSize = coordinatesSize - forwardPathSize;
                    backwardPath.reserve(backwardPathSize + 1); //Extra space for the split point
                    
                    //Forward path starts with the split point
                    forwardPath.emplace_back(closestPointOnRoute);
                    
                    for (int i = 0; i < coordinatesSize; i++)
                    {
                        if (IsEqual(closestPointOnRoute, coordinates[i]))
                        {
                            continue;
                        }
                        
                        if(i<=splitIndex)
                        {
                            backwardPath.emplace_back(coordinates[i]);
                        }
                        else
                        {
                            forwardPath.emplace_back(coordinates[i]);
                        }
                    }
                    
                    //Backward path ends with the split point
                    backwardPath.emplace_back(closestPointOnRoute);
                    
                    if(backwardPath.size()>1)
                    {
                        routeLines.emplace_back(CreatePolyline(backwardPath,
                                                               backwardColor,
                                                               directionModel.GetIsIndoors(),
                                                               directionModel.GetIndoorMapId().Value(),
                                                               directionModel.GetIndoorMapFloorId()));
                    }
                    
                    if(forwardPath.size()>1)
                    {
                        routeLines.emplace_back(CreatePolyline(forwardPath,
                                                               forwardColor,
                                                               directionModel.GetIsIndoors(),
                                                               directionModel.GetIndoorMapId().Value(),
                                                               directionModel.GetIndoorMapFloorId()));
                    }
                    
                    return routeLines;
                }
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForFloorTransition(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                const std::string& indoorMapId,
                                                                                int floorBefore,
                                                                                int floorAfter,
                                                                                const Eegeo::v4& color)
            {
                double verticalLineHeight = 5.0;
                double lineHeight = (floorAfter > floorBefore) ? verticalLineHeight : -verticalLineHeight;
                RouteLines routeLines;

                uint coordinateCount = static_cast<uint>(coordinates.size());
                Eegeo_ASSERT(coordinateCount >= 2, "Can't make a floor transition line with a single point");
                std::vector<Eegeo::Space::LatLong> startCoords;
                startCoords.push_back(coordinates.at(0));
                startCoords.push_back(coordinates.at(1));
                std::vector<Eegeo::Space::LatLong> endCoords;
                endCoords.push_back(coordinates.at(coordinateCount-2));
                endCoords.push_back(coordinates.at(coordinateCount-1));

                routeLines.push_back(MakeVerticalLine(startCoords, indoorMapId, floorBefore, 0, lineHeight, color));
                routeLines.push_back(MakeVerticalLine(endCoords, indoorMapId, floorAfter, -lineHeight, 0, color));
                return routeLines;
            }
            
            PolyLineArgs::ShapeModel::IdType NavRoutingPolylineFactory::MakeVerticalLine(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                         const std::string& indoorMapId,
                                                                                         int floor,
                                                                                         double heightStart,
                                                                                         double heightEnd,
                                                                                         const Eegeo::v4& color)
            {
                std::vector<double> perPointElevations;
                perPointElevations.push_back(heightStart);
                perPointElevations.push_back(heightEnd);
                
                return CreatePolyline(coordinates, color, true, indoorMapId, floor, true, perPointElevations);
            }
            
            PolyLineArgs::ShapeModel::IdType NavRoutingPolylineFactory::CreatePolyline(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                        const Eegeo::v4& color,
                                                                                        bool isIndoors,
                                                                                        const std::string& indoorMapId,
                                                                                        int indoorMapFloorId,
                                                                                        bool hasPerPointElevation,
                                                                                        const std::vector<double>& perPointElevations)
            {
                Eegeo::Shapes::Polylines::PolylineShapeBuilder shapeBuilder;
                shapeBuilder.SetCoordinates(coordinates)
                            .SetFillColor(color)
                            .SetThickness(m_routeThickness)
                            .SetMiterLimit(m_miterLimit)
                            .SetElevation(m_routeElevation)
                            .SetElevationMode(m_routeElevationMode)
                            .SetShouldScaleWithMap(m_shouldScaleWithMap);
                
                if (isIndoors)
                {
                    shapeBuilder.SetIndoorMap(indoorMapId, indoorMapFloorId);
                }
                
                if (hasPerPointElevation)
                {
                    shapeBuilder.SetPerPointElevations(perPointElevations);
                }
                
                return m_shapeService.Create(shapeBuilder.Build());
            }
        }
    }
}
