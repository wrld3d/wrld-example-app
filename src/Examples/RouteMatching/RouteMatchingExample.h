//
//  RouteMatchingExample.h
//  ExampleApp
//
//  Created by Scott on 16/01/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteMatchingExample__
#define __ExampleApp__RouteMatchingExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "IRouteMatchingExampleViewFactory.h"
#include "IRouteMatchingExampleView.h"
#include "UIActionHandler.h"

namespace Examples
{
    class RouteMatchingExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::EegeoWorld& m_world;
        
        const IRouteMatchingExampleViewFactory& m_routeMatchingViewFactory;
        UIActionHandler<RouteMatchingExample> m_toggleRouteMatchingHandler;
        IRouteMatchingExampleView* m_pRouteMatchingView;
        
        bool m_createdRoutes;
        bool m_routesMatchedToNavigationGraph;
        std::vector<Eegeo::Routes::Route*> m_routes;
        Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
        
        void CreateRoutes(bool shouldMatchToNavigationGraph);
        void DestroyRoutes();
        void CreateAndBindUI();
        
    public:
        RouteMatchingExample(Eegeo::Routes::RouteService& routeService,
                             Eegeo::EegeoWorld& eegeoWorld,
                             const IRouteMatchingExampleViewFactory& routeMatchingViewFactory);
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
        
        void ToggleMatching();
    };
}

#endif /* defined(__ExampleApp__RouteMatchingExample__) */
