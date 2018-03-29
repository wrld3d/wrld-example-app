// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WrldJourneys/JourneysModel.h"

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
                NavUIViewRouteUpdateHandler(JourneysModel* journeysModel,
                                            NavRouteDrawingController& routeDrawingController,
                                            NavRoutingServiceController& routingServiceController);
                
                ~NavUIViewRouteUpdateHandler();
                
                void UpdateRoute();
                void ClearRoute();
                
            private:
                void OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results);
                
                JourneysModel* m_journeysModel;
                NavRouteDrawingController& m_routeDrawingController;
                NavRoutingServiceController& m_routingServiceController;
                
                Eegeo::Helpers::TCallback1<NavUIViewRouteUpdateHandler, const std::vector<Eegeo::Routes::Webservice::RouteData>> m_routesReceivedCallback;
            };
        }
    }
}
