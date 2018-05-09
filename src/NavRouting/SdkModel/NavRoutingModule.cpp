// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModule.h"

#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingModule::NavRoutingModule(Eegeo::Routes::RouteService& routeService,
                                               Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice)
            {
                m_pNavRouteDrawingController = Eegeo_NEW(NavRouteDrawingController)(routeService);
                m_pNavRoutingServiceController = Eegeo_NEW(NavRoutingServiceController)(routingWebservice);
            }

            NavRoutingModule::~NavRoutingModule()
            {
                Eegeo_DELETE m_pNavRouteDrawingController;
                Eegeo_DELETE m_pNavRoutingServiceController;
            }
            
            NavRouteDrawingController& NavRoutingModule::GetRouteDrawingController()
            {
                return *m_pNavRouteDrawingController;
            }

            INavRoutingServiceController& NavRoutingModule::GetRoutingServiceController()
            {
                return *m_pNavRoutingServiceController;
            }
        }
    }
}
