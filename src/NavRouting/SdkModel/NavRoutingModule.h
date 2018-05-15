// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "NavRouting.h"
#include "RouteService.h"
#include "IRoutingWebservice.h"
#include "ILocationService.h"
#include "NavRoutingController.h"
#include "NavRoutingModel.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingModule : private Eegeo::NonCopyable
            {
            public:
                
                NavRoutingModule(PolyLineArgs::IShapeService& shapeService,
                                 Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                 Eegeo::Location::ILocationService& locationService,
                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~NavRoutingModule();


                INavRouteDrawingController& GetRouteDrawingController();
                INavRoutingServiceController& GetRoutingServiceController();
                
            private:

                NavRoutingModel* m_pNavRoutingModel;
                NavRouteDrawingController* m_pNavRouteDrawingController;
                NavRoutingServiceController* m_pNavRoutingServiceController;
                NavWidgetRouteUpdateHandler* m_pRouteUpdateHandler;
                NavWidgetRouteDrawingHandler* m_pRouteDrawingHandler;
                NavRoutingController* m_pRoutingController;
            };
        }
    }
}
