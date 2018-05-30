// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingController.h"
#include "MarkerBuilder.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRouteDrawingController::NavRouteDrawingController(INavRoutingModel& navRoutingModel,
                                                                 INavRoutingPolylineFactory& polylineFactory,
                                                                 PolyLineArgs::IShapeService& shapeService,
                                                                 Eegeo::Markers::IMarkerService& markerService)
            : m_navRoutingModel(navRoutingModel)
            , m_polylineFactory(polylineFactory)
            , m_shapeService(shapeService)
            , m_markerService(markerService)
            {

            }

            NavRouteDrawingController::~NavRouteDrawingController()
            {
                ClearRoute();
            }
            
            

            void NavRouteDrawingController::DrawRoute(const Eegeo::v4& color)
            {
                NavRoutingRouteModel routeModel;
                NavRoutingLocationModel startLocation;
                NavRoutingLocationModel endLocation;
                if(m_navRoutingModel.TryGetRoute(routeModel),
                   m_navRoutingModel.TryGetStartLocation(startLocation),
                   m_navRoutingModel.TryGetEndLocation(endLocation))
                {
                    
                    
                    AddPin("Start",
                           startLocation.GetIsIndoors(),
                           startLocation.GetIndoorMapId().Value(),
                           startLocation.GetIndoorMapFloorId(),
                           startLocation.GetLatLon(),
                           "aroundme",
                           0);
                    
                    const auto& directions = routeModel.GetDirections();
                    for (int i = 0; i < directions.size(); ++i)
                    {
                        
                        DrawRouteForStep(i, directions, color);
                    }
                    
                    AddPin("Finish",
                           endLocation.GetIsIndoors(),
                           endLocation.GetIndoorMapId().Value(),
                           endLocation.GetIndoorMapFloorId(),
                           endLocation.GetLatLon(),
                           "aroundme",
                           0);
                }
            }
            
            void NavRouteDrawingController::ClearRoute()
            {
                for(const auto& routeIt : m_routes)
                {
                    DestroyLines(routeIt.second);
                }
                
                ClearPins();
                m_routes.clear();
            }
            
            void NavRouteDrawingController::SetRouteStepColor(int step,
                                                              const Eegeo::v4& color)
            {
                NavRoutingRouteModel routeModel;
                if(m_navRoutingModel.TryGetRoute(routeModel))
                {
                    if (m_routes.find(step)!=m_routes.end())
                    {
                        DestroyLines(m_routes[step]);
                        DrawRouteForStep(step, routeModel.GetDirections(), color);
                    }
                }
            }

            void NavRouteDrawingController::UpdateRouteStepProgress(int step,
                                                                    const Eegeo::v4& colorForCrossedPath,
                                                                    const Eegeo::v4& colorForUpcomingPath,
                                                                    int splitIndex,
                                                                    const Eegeo::Space::LatLong& closestPointOnRoute)
            {
                NavRoutingRouteModel routeModel;
                if(m_navRoutingModel.TryGetRoute(routeModel))
                {
                    if (m_routes.find(step)!=m_routes.end())
                    {
                        const auto& polylines = m_routes[step];
                        
                        DestroyLines(polylines);
                        
                        DrawRouteForStep(step,
                                         routeModel.GetDirections(),
                                         colorForUpcomingPath,
                                         colorForCrossedPath,
                                         splitIndex,
                                         closestPointOnRoute);
                    }
                }
            }
            
            void NavRouteDrawingController::DrawRouteForStep(int step,
                                                             const std::vector<NavRoutingDirectionModel>& directions,
                                                             const Eegeo::v4& color)
            {
                const NavRoutingDirectionModel& directionModel = directions[step];
                
                if (directionModel.GetPath().size() < 2)
                {
                    return;
                }
                
                if (directionModel.GetIsMultiFloor())
                {
                    bool isValidTransition = step > 0 && step < (directions.size() - 1) && directionModel.GetIsIndoors();
                    
                    if (!isValidTransition)
                    {
                        return;
                    }
                    
                    const NavRoutingDirectionModel& directionBefore = directions[step-1];
                    const NavRoutingDirectionModel& directionAfter = directions[step+1];
                    
                    m_routes[step] = m_polylineFactory.CreateLinesForFloorTransition(directionModel.GetPath(),
                                                                                  directionModel.GetIndoorMapId().Value(),
                                                                                  directionBefore.GetIndoorMapFloorId(),
                                                                                  directionAfter.GetIndoorMapFloorId(),
                                                                                  color);
                }
                else
                {
                    m_routes[step] = m_polylineFactory.CreateLinesForRouteDirection(directionModel, color);
                }
            }
            
            void NavRouteDrawingController::DrawRouteForStep(int step,
                                                             const std::vector<NavRoutingDirectionModel>& directions,
                                                             const Eegeo::v4& forwardColor,
                                                             const Eegeo::v4& backwardColor,
                                                             int splitIndex,
                                                             const Eegeo::Space::LatLong& closestPointOnRoute)
            {
                const NavRoutingDirectionModel& directionModel = directions[step];
                
                if (directionModel.GetPath().size() < 2)
                {
                    return;
                }
                
                if (directionModel.GetIsMultiFloor())
                {
                    bool hasReachedEnd = splitIndex == (directionModel.GetPath().size()-1);
                    DrawRouteForStep(step, directions, hasReachedEnd? backwardColor : forwardColor);
                }
                else
                {
                    m_routes[step] = m_polylineFactory.CreateLinesForRouteDirection(directionModel,
                                                                                    forwardColor,
                                                                                    backwardColor,
                                                                                    splitIndex,
                                                                                    closestPointOnRoute);
                }
            }
            
            void NavRouteDrawingController::DestroyLines(RouteLines lines)
            {
                for (const auto& shapeId : lines)
                {
                    m_shapeService.Destroy(shapeId);
                }
                
                lines.clear();
            }
            
            void NavRouteDrawingController::AddPin(std::string title,
                                                   bool interior,
                                                   const std::string& buildingID,
                                                   const int& buildingFloor,
                                                   const Eegeo::Space::LatLong& location,
                                                   const std::string& pinIconKey,
                                                   float heightAboveTerrainMetres,
                                                   std::string identifier,
                                                   std::string labelStyleName)
            {
                
                const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                    .SetLabelText(title)
                    .SetLabelIcon("general")
                    .SetElevation(heightAboveTerrainMetres)
                    // temp workaround to specify interior floor by zero-based index rather than 'floor number' id (MPLY-8062)
                    .SetInteriorWithFloorIndex(buildingID, buildingFloor)
                    .SetLabelStyle("selected_default")
                    .SetSubPriority(1)
                    .Build();
                
                const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);

                const auto& markerCreateParamsHighlight = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                    .SetLabelText("")
                    .SetLabelIcon("selected_pin")
                    .SetElevation(heightAboveTerrainMetres)
                    // temp workaround to specify interior floor by zero-based index rather than 'floor number' id (MPLY-8062)
                    .SetInteriorWithFloorIndex(buildingID, buildingFloor)
                    .SetLabelStyle("selected_default")
                    .SetSubPriority(0)
                    .Build();

                const Eegeo::Markers::IMarker::IdType markerIdHighlight = m_markerService.Create(markerCreateParamsHighlight);
                
                m_markerIDs.push_back(markerId);
                m_markerIDs.push_back(markerIdHighlight);
            }
            
            void NavRouteDrawingController::ClearPins()
            {
                while(!m_markerIDs.empty())
                {
                    m_markerService.Destroy(m_markerIDs.back());
                    m_markerIDs.pop_back();
                }
                
            }
        }
    }
}
