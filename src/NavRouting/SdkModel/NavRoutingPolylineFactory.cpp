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
                bool AreApproximatelyEqual(
                    const Eegeo::Space::LatLong& first,
                    const Eegeo::Space::LatLong& second
                )
                {
                    // <= 1mm separation
                    const double epsilonSq = 1e-6;
                    return first.ToECEF().SquareDistanceTo(second.ToECEF()) <= epsilonSq;
                }

                bool AreCoordinateElevationPairApproximatelyEqual(
                    std::pair<Eegeo::Space::LatLong, double>& a,
                    std::pair<Eegeo::Space::LatLong, double>& b
                    )
                {
                    const double elevationEpsilon = 1e-3;

                    if (!AreApproximatelyEqual(a.first, b.first))
                    {
                        return false;
                    }

                    return std::abs(a.second - b.second) <= elevationEpsilon;
                }

                void RemoveCoincidentPoints(std::vector<Eegeo::Space::LatLong>& coordinates)
                {
                    coordinates.erase(
                        std::unique(coordinates.begin(), coordinates.end(), AreApproximatelyEqual),
                        coordinates.end());
                }

                void RemoveCoincidentPointsWithElevations(
                    std::vector<Eegeo::Space::LatLong>& coordinates,
                    std::vector<double>& perPointElevations
                )
                {
                    Eegeo_ASSERT(coordinates.size() == perPointElevations.size());
                    std::vector<std::pair<Eegeo::Space::LatLong, double>> zipped;
                    zipped.reserve(coordinates.size());
                    for (int i = 0; i < coordinates.size(); ++i)
                    {
                        zipped.push_back(std::make_pair(coordinates[i], perPointElevations[i]));
                    }

                    const auto newEnd = std::unique(zipped.begin(), zipped.end(), AreCoordinateElevationPairApproximatelyEqual);
                    if (newEnd != zipped.end())
                    {
                        zipped.erase(newEnd, zipped.end());

                        coordinates.clear();
                        perPointElevations.clear();

                        for (const auto& pair : zipped)
                        {
                            coordinates.push_back(pair.first);
                            perPointElevations.push_back(pair.second);
                        }
                    }

                }

                NavRoutingPolylineCreateParams MakeNavRoutingPolylineCreateParams(
                    const std::vector<Eegeo::Space::LatLong>& coordinates,
                    const Eegeo::v4& color,
                    const std::string& indoorMapId,
                    int indoorMapFloorId
                )
                {
                    return {coordinates, color, indoorMapId, indoorMapFloorId, {}};
                }

                NavRoutingPolylineCreateParams MakeNavRoutingPolylineCreateParamsForVerticalLine(
                    const std::vector<Eegeo::Space::LatLong>& coordinates,
                    const Eegeo::v4& color,
                    const std::string& indoorMapId,
                    int indoorMapFloorId,
                    double heightStart,
                    double heightEnd
                )
                {
                    return {coordinates, color, indoorMapId, indoorMapFloorId, {heightStart, heightEnd}};
                }


                bool CanAmalgamate(
                    const NavRoutingPolylineCreateParams& a,
                    const NavRoutingPolylineCreateParams& b
                )
                {
                    if (a.IsIndoor() != b.IsIndoor())
                    {
                        return false;
                    }

                    if (a.GetIndoorMapId() != b.GetIndoorMapId())
                    {
                        return false;
                    }

                    if (a.GetIndoorMapFloorId() != b.GetIndoorMapFloorId())
                    {
                        return false;
                    }

                    if (a.GetColor() != b.GetColor())
                    {
                        return false;
                    }
                    return true;
                }

                std::vector<std::pair<int, int>> BuildAmalgamationRanges(const std::vector<NavRoutingPolylineCreateParams>& polylineCreateParams)
                {
                    std::vector<std::pair<int, int>> ranges;

                    if (polylineCreateParams.empty())
                    {
                        return ranges;
                    }

                    int rangeStart = 0;
                    for (int i = 1; i < polylineCreateParams.size(); ++i)
                    {
                        const auto &a = polylineCreateParams[i - 1];
                        const auto &b = polylineCreateParams[i];

                        if (!CanAmalgamate(a, b))
                        {
                            ranges.push_back(std::make_pair(rangeStart, i));
                            rangeStart = i;
                        }
                    }
                    ranges.push_back(std::make_pair(rangeStart, int(polylineCreateParams.size())));

                    return ranges;
                }
            }
            
            NavRoutingPolylineFactory::NavRoutingPolylineFactory(
                PolyLineArgs::IShapeService& shapeService,
                const NavRoutingPolylineConfig& polylineConfig
            )
            : m_shapeService(shapeService)
            , m_polylineConfig(polylineConfig)
            {
                
            }

            std::vector<NavRoutingPolylineCreateParams> NavRoutingPolylineFactory::CreateLinesForRouteDirection(
                const NavRoutingDirectionModel& directionModel,
                const Eegeo::v4& color
                )
            {
                std::vector<NavRoutingPolylineCreateParams> results;
                std::vector<Eegeo::Space::LatLong> uniqueCoordinates(directionModel.GetPath());
                RemoveCoincidentPoints(uniqueCoordinates);

                if(uniqueCoordinates.size()>1)
                {
                    results.push_back(MakeNavRoutingPolylineCreateParams(
                        uniqueCoordinates,
                        color,
                        directionModel.GetIndoorMapId().Value(),
                        directionModel.GetIndoorMapFloorId())
                    );
                }
                
                return results;
            }

            std::vector<NavRoutingPolylineCreateParams> NavRoutingPolylineFactory::CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
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
                    std::vector<NavRoutingPolylineCreateParams> results;
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

                    RemoveCoincidentPoints(backwardPath);
                    RemoveCoincidentPoints(forwardPath);

                    if(backwardPath.size()>1)
                    {
                        results.emplace_back(MakeNavRoutingPolylineCreateParams(
                            backwardPath,
                            backwardColor,
                            directionModel.GetIndoorMapId().Value(),
                            directionModel.GetIndoorMapFloorId())
                        );
                    }
                    
                    if(forwardPath.size()>1)
                    {
                        results.emplace_back(MakeNavRoutingPolylineCreateParams(
                            forwardPath,
                            forwardColor,
                            directionModel.GetIndoorMapId().Value(),
                            directionModel.GetIndoorMapFloorId())
                        );
                    }
                    
                    return results;
                }
            }

            std::vector<NavRoutingPolylineCreateParams> NavRoutingPolylineFactory::CreateLinesForFloorTransition(
                const std::vector<Eegeo::Space::LatLong>& coordinates,
                const std::string& indoorMapId,
                int floorBefore,
                int floorAfter,
                const Eegeo::v4& color
            )
            {
                double verticalLineHeight = 5.0;
                double lineHeight = (floorAfter > floorBefore) ? verticalLineHeight : -verticalLineHeight;
                std::vector<NavRoutingPolylineCreateParams> results;

                uint coordinateCount = static_cast<uint>(coordinates.size());
                Eegeo_ASSERT(coordinateCount >= 2, "Can't make a floor transition line with a single point");
                std::vector<Eegeo::Space::LatLong> startCoords;
                startCoords.push_back(coordinates.at(0));
                startCoords.push_back(coordinates.at(1));
                std::vector<Eegeo::Space::LatLong> endCoords;
                endCoords.push_back(coordinates.at(coordinateCount-2));
                endCoords.push_back(coordinates.at(coordinateCount-1));

                results.push_back(MakeNavRoutingPolylineCreateParamsForVerticalLine(startCoords, color, indoorMapId, floorBefore, 0, lineHeight));
                results.push_back(MakeNavRoutingPolylineCreateParamsForVerticalLine(endCoords, color, indoorMapId, floorAfter, -lineHeight, 0));
                return results;
            }

            RoutePolylineIdVector NavRoutingPolylineFactory::CreatePolylines(const std::vector<NavRoutingPolylineCreateParams>& polylineCreateParams)
            {
                RoutePolylineIdVector result;

                const auto& ranges = BuildAmalgamationRanges(polylineCreateParams);

                for (const auto& range : ranges)
                {
                    const auto& polylineIds = CreateAmalgamatedPolylinesForRange(polylineCreateParams, range.first, range.second);
                    result.insert(result.end(), polylineIds.begin(), polylineIds.end());
                }

                return result;
            }

            RoutePolylineIdVector NavRoutingPolylineFactory::CreateAmalgamatedPolylinesForRange(
                const std::vector<NavRoutingPolylineCreateParams>& polylineCreateParams,
                const int rangeStartIndex,
                const int rangeEndIndex
            )
            {
                Eegeo_ASSERT(rangeStartIndex < rangeEndIndex);
                Eegeo_ASSERT(rangeStartIndex >= 0);
                Eegeo_ASSERT(rangeEndIndex <= polylineCreateParams.size());

                RoutePolylineIdVector result;

                std::vector<Eegeo::Space::LatLong> joinedCoordinates;
                std::vector<double> joinedPerPointElevations;
                bool anyPerPointElevations = false;

                for (int i = rangeStartIndex; i < rangeEndIndex; ++i)
                {
                    const auto& params = polylineCreateParams[i];
                    const auto& coordinates = params.GetCoordinates();

                    joinedCoordinates.insert(joinedCoordinates.end(), coordinates.begin(), coordinates.end());

                    if (!params.GetPerPointElevations().empty())
                    {
                        anyPerPointElevations = true;
                    }
                }

                if (anyPerPointElevations)
                {
                    for (int i = rangeStartIndex; i < rangeEndIndex; ++i)
                    {
                        const auto& params = polylineCreateParams[i];
                        const auto& perPointElevations = params.GetPerPointElevations();

                        if (perPointElevations.empty())
                        {
                            // fill with zero
                            joinedPerPointElevations.insert(joinedPerPointElevations.end(), params.GetCoordinates().size(), 0.0);
                        }
                        else
                        {
                            joinedPerPointElevations.insert(joinedPerPointElevations.end(), perPointElevations.begin(), perPointElevations.end());
                        }
                    }

                    RemoveCoincidentPointsWithElevations(joinedCoordinates, joinedPerPointElevations);
                }
                else
                {
                    RemoveCoincidentPoints(joinedCoordinates);
                }

                if (joinedCoordinates.size() > 1)
                {
                    const auto& commonParams = polylineCreateParams[rangeStartIndex];
                    const auto& polylineParams = Eegeo::Shapes::Polylines::PolylineShapeBuilder()
                        .SetCoordinates(joinedCoordinates)
                        .SetPerPointElevations(joinedPerPointElevations)
                        .SetIndoorMap(commonParams.GetIndoorMapId(), commonParams.GetIndoorMapFloorId())
                        .SetFillColor(commonParams.GetColor())
                        .SetThickness(m_polylineConfig.routeThickness)
                        .SetMiterLimit(m_polylineConfig.miterLimit)
                        .SetElevation(m_polylineConfig.routeElevation)
                        .SetElevationMode(m_polylineConfig.routeElevationMode)
                        .SetShouldScaleWithMap(m_polylineConfig.shouldScaleWithMap)
                        .Build();

                    const auto& polylineId = m_shapeService.Create(polylineParams);
                    result.push_back(polylineId);
                }

                return result;
            }
        }
    }
}
