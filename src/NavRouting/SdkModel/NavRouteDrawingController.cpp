// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRouteDrawingController.h"

#include "VectorMath.h"
#include "RouteBuilder.h"
#include "RouteStyle.h"
#include "RouteVertex.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            std::vector<Eegeo::Routes::RouteVertex> BuildRoute(const std::vector<NavRouteDrawingVertexData>& verts)
            {
                const Eegeo::v4 color(1, 0, 0, 0.8f);
                float halfWidth = 5.f;
                float velocity = 20.f;
                
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
            :m_routeService(routeService)
            {
                m_pRoute = NULL;
            }

            NavRouteDrawingController::~NavRouteDrawingController()
            {
                ClearRoute();
            }
            
            void NavRouteDrawingController::DrawRoute(const std::vector<NavRouteDrawingVertexData>& verts)
            {
                std::vector<Eegeo::Routes::RouteVertex> points = BuildRoute(verts);
                
                Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
                
                m_pRoute = m_routeService.CreateRoute(points, routeStyle, false);
                
            }
            
            void NavRouteDrawingController::ClearRoute()
            {
                if (m_pRoute!=NULL)
                {
                    m_routeService.DestroyRoute(m_pRoute);
                    m_pRoute = NULL;
                }
            }
            
            void NavRouteDrawingController::SetCurrentStep(int stepIndex)
            {
                //TODO implement highlighting of current step
            }
        }
    }
}
