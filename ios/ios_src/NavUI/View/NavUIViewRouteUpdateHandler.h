// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WrldNav/WrldNav.h"

#include "Types.h"
#include "NavRouting.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"

#include <vector>

using namespace ExampleApp::NavRouting::SdkModel;

namespace ExampleApp
{
    namespace NavUI
    {
        namespace View
        {
            class NavUIViewRouteUpdateHandler: private Eegeo::NonCopyable
            {
            public:
                NavUIViewRouteUpdateHandler(WRLDNavModel* navModel,
                                            NavRoutingServiceController& routingServiceController);
                
                ~NavUIViewRouteUpdateHandler();
                
                void UpdateRoute();
                
            private:
                void OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results);
                
                WRLDNavModel* m_navModel;
                NavRoutingServiceController& m_routingServiceController;
                
                Eegeo::Helpers::TCallback1<NavUIViewRouteUpdateHandler, const std::vector<Eegeo::Routes::Webservice::RouteData>> m_routesReceivedCallback;
            };
        }
    }
}
