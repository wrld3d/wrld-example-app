//
//  RouteThicknessPolicyExample.h
//  ExampleApp
//
//  Created by Scott on 28/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteThicknessPolicyExample__
#define __ExampleApp__RouteThicknessPolicyExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"

namespace Examples
{
    class RouteThicknessPolicyExample : public IExample
    {
    private:
        class MyScalingRouteThicknessPolicy : public Eegeo::Routes::IRouteThicknessPolicy
        {
            float m_scale;
            bool m_scaledown;
            float GetThicknessScale() const;
        public:
            MyScalingRouteThicknessPolicy():m_scale(1.f), m_scaledown(false) {}
            void UpdateScale();
        };
        
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::EegeoWorld& m_world;
        
        bool m_createdRoutes;
        std::vector<Eegeo::Routes::Route*> m_routes;
        Eegeo::Routes::IdentityRouteThicknessPolicy m_identityRouteThicknessPolicy;
        Eegeo::Routes::LinearAltitudeBasedRouteThicknessPolicy m_linearAltitudeBasedRouteThicknessPolicy;
        MyScalingRouteThicknessPolicy m_myScalingRouteThicknessPolicy;
        
    public:
        RouteThicknessPolicyExample(Eegeo::Routes::RouteService& routeService,
                                    Eegeo::Rendering::RenderContext& renderContext,
                                    Eegeo::EegeoWorld& eegeoWorld);
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__RouteThicknessPolicyExample__) */
