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
            struct VertexDto
            {
                VertexDto(double latitudeDegrees, double longitudeDegrees, const std::string& indoorMapId, int indoorMapFloorId, bool multiFloor)
                : m_latitudeDegrees(latitudeDegrees)
                , m_longitudeDegrees(longitudeDegrees)
                , m_indoorMapId(indoorMapId)
                , m_indoorMapFloorId(indoorMapFloorId)
                , m_multiFloor(multiFloor)
                {
                }
                
                bool operator != (const VertexDto& rhs) const
                {
                    return m_latitudeDegrees != rhs.m_latitudeDegrees ||
                    m_longitudeDegrees != rhs.m_longitudeDegrees ||
                    m_indoorMapId != rhs.m_indoorMapId ||
                    m_indoorMapFloorId != rhs.m_indoorMapFloorId ||
                    m_multiFloor != rhs.m_multiFloor;
                }
                
                bool operator == (const VertexDto& rhs) const
                {
                    return !(*this != rhs);
                }
                
                double GetLatitudeDegrees() const { return m_latitudeDegrees; }
                double GetLongitudeDegrees() const { return m_longitudeDegrees; }
                const std::string& GetIndoorMapId() const { return m_indoorMapId; }
                int GetIndoorMapFloorId() const { return m_indoorMapFloorId; }
                bool IsMultiFloor() const { return m_multiFloor; }
            private:
                double m_latitudeDegrees;
                double m_longitudeDegrees;
                std::string m_indoorMapId;
                int m_indoorMapFloorId;
                bool m_multiFloor;
            };
            
            std::vector<Eegeo::Routes::RouteVertex> BuildRoute(const Eegeo::Routes::Webservice::RouteData& route)
            {
                std::vector<VertexDto> verts;
                
                for (auto& section: route.Sections)
                {
                    for (auto& step: section.Steps)
                    {
                        for (auto& latLng: step.Path)
                        {
                            verts.emplace_back(latLng.GetLatitudeInDegrees(), latLng.GetLongitudeInDegrees(), step.IndoorId, step.IndoorFloorId, step.IsMultiFloor);
                        }
                    }
                }
                
                verts.erase(std::unique(verts.begin(), verts.end()), verts.end());
                
                
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
            
            void NavRouteDrawingController::DrawRoute(const Eegeo::Routes::Webservice::RouteData& routeData)
            {
                std::vector<Eegeo::Routes::RouteVertex> points = BuildRoute(routeData);
                
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
