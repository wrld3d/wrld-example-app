// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Routes.h"
#include "RouteService.h"
#include "IdentityRouteThicknessPolicy.h"
#include "NavRouteDrawingVertexData.h"
#include "VectorMath.h"

#include <vector>
#include <unordered_map>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRouteDrawingController : private Eegeo::NonCopyable
            {
            public:
                NavRouteDrawingController(Eegeo::Routes::RouteService& routeService);

                ~NavRouteDrawingController();
                
                void AddRoute(int routeStep, const std::vector<NavRouteDrawingVertexData>& vertsData, Eegeo::v4 color);
                
                void ClearRoute();
                
                void SetRouteColor(int routeStep, Eegeo::v4 color);
                
            private:
                Eegeo::Routes::Route* BuildRoute(const std::vector<Eegeo::Routes::RouteVertex>& points);
                
                Eegeo::Routes::RouteService& m_routeService;
                std::unordered_map<int, Eegeo::Routes::Route*> m_routes;
                Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
                
                float m_halfWidth;
                float m_velocity;
            };
        }
    }
}
