// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "NavRouting.h"
#include "RouteService.h"
#include "IRoutingWebservice.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingModule : private Eegeo::NonCopyable
            {
            public:
                
                NavRoutingModule(Eegeo::Routes::RouteService& routeService,
                                 Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice);

                ~NavRoutingModule();
                
                NavRouteDrawingController& GetRouteDrawingController();
                NavRoutingServiceController& GetRoutingServiceController();
                
            private:
                
                NavRouteDrawingController* m_pNavRouteDrawingController;
                NavRoutingServiceController* m_pNavRoutingServiceController;
            };
        }
    }
}
