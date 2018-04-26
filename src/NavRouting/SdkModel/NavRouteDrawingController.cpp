// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingController.h"

#include "Route.h"
#include "RouteBuilder.h"
#include "RouteStyle.h"
#include "RouteVertex.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            std::vector<Eegeo::Routes::RouteVertex> BuildRoutePoints(const std::vector<NavRouteDrawingVertexData>& verts, Eegeo::v4 color, float halfWidth, float velocity)
            {
                Eegeo::Routes::RouteBuilder builder;
                builder.Start(color, halfWidth, velocity, Eegeo::Routes::Pedestrian);
                
                for (const auto& vert: verts)
                {
                    if (!vert.IsMultiFloor())
                    {
                        builder.ChangeIndoorMapFloor(vert.GetIndoorMapFloorId());
                        // see MPLY-8747
                        // for multifloor vertices, vert.GetIndoorMapFloorId() is always 0, retain builder's previous floor value
                    }
                    builder.ChangeIndoorMap(vert.GetIndoorMapId());
                    builder.AddPoint(vert.GetLatitudeDegrees(), vert.GetLongitudeDegrees());
                }
                
                return builder.FinishRoute();
            }
            
            NavRouteDrawingController::NavRouteDrawingController(Eegeo::Routes::RouteService& routeService)
            : m_routeService(routeService)
            , m_halfWidth(5.f)
            , m_velocity(20.f)
            {
            }

            NavRouteDrawingController::~NavRouteDrawingController()
            {
                ClearRoute();
            }
            
            void NavRouteDrawingController::AddRoute(int routeStep, const std::vector<NavRouteDrawingVertexData>& vertsData, Eegeo::v4 color)
            {
                std::vector<Eegeo::Routes::RouteVertex> points = BuildRoutePoints(vertsData, color, m_halfWidth, m_velocity);
                
                Eegeo::Routes::Route* route = BuildRoute(points);
                m_routes[routeStep] = route;
            }
            
            void NavRouteDrawingController::ClearRoute()
            {
                for(const auto& routeIt : m_routes)
                {
                    m_routeService.DestroyRoute(routeIt.second);
                }
                
                m_routes.clear();
            }
            
            void NavRouteDrawingController::SetRouteColor(int routeStep, Eegeo::v4 color)
            {
                if (m_routes.find(routeStep)!=m_routes.end())
                {
                    Eegeo::Routes::Route* oldRoute = m_routes[routeStep];
                    
                    const std::vector<Eegeo::Routes::RouteVertex>& oldPoints = oldRoute->GetPoints();
                    
                    std::vector<Eegeo::Routes::RouteVertex> newPoints;
                    newPoints.reserve(oldPoints.size());
                    
                    for (const auto& vert: oldPoints)
                    {
                        newPoints.emplace_back(vert.GetLocation(),
                                               vert.GetIndoorMapId(),
                                               vert.GetIndoorMapFloorId(),
                                               color,
                                               vert.GetHalfWidth(),
                                               vert.GetSpeed(),
                                               vert.GetRouteVertexClassification(),
                                               vert.GetDistanceFromStartInMetres(),
                                               vert.GetRouteParam());
                    }
                    
                    m_routeService.DestroyRoute(oldRoute);
                    Eegeo::Routes::Route* newRoute = BuildRoute(newPoints);
                    m_routes[routeStep] = newRoute;
                }
            }
            
            Eegeo::Routes::Route* NavRouteDrawingController::BuildRoute(const std::vector<Eegeo::Routes::RouteVertex>& points)
            {
                Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
                
                return m_routeService.CreateRoute(points, routeStyle, false);
            }
        }
    }
}
