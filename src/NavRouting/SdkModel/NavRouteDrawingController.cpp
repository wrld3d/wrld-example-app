// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRouteDrawingController::NavRouteDrawingController(INavRoutingModel& navRoutingModel,
                                                                 INavRoutingPolylineFactory& polylineFactory,
                                                                 PolyLineArgs::IShapeService& shapeService)
            : m_navRoutingModel(navRoutingModel)
            , m_polylineFactory(polylineFactory)
            , m_shapeService(shapeService)
            {

            }

            NavRouteDrawingController::~NavRouteDrawingController()
            {
                ClearRoute();
            }
            
            void NavRouteDrawingController::DrawRoute(const Eegeo::v4& color)
            {
                NavRoutingRouteModel routeModel;
                if(m_navRoutingModel.TryGetRoute(routeModel))
                {
                    const auto& directions = routeModel.GetDirections();
                    for (int i = 0; i < directions.size(); ++i)
                    {
                        DrawRouteForStep(i, directions, color);
                    }
                }
            }
            
            void NavRouteDrawingController::ClearRoute()
            {
                for(const auto& routeIt : m_routes)
                {
                    DestroyLines(routeIt.second);
                }

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
        }
    }
}
