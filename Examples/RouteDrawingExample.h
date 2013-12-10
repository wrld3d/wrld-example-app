//
//  RouteDrawingExample.h
//  ExampleApp
//
//  Created by Scott on 14/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteDrawingExample__
#define __ExampleApp__RouteDrawingExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"

namespace Examples
{
    class RouteDrawingExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::EegeoWorld& m_world;
        
        bool m_createdRoutes;
        std::vector<Eegeo::Routes::Route*> m_routes;
        Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
        
    public:
        RouteDrawingExample(Eegeo::Routes::RouteService& routeService,
                            Eegeo::EegeoWorld& eegeoWorld);
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}



#endif /* defined(__ExampleApp__RouteDrawingExample__) */
