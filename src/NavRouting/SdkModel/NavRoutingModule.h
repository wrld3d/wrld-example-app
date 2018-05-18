// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AlertBox.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "NavRouting.h"
#include "Routes.h"
#include "Location.h"

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
                                 Eegeo::Location::NavigationService& navigationService,
                                 Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~NavRoutingModule();

                void Update(float dt);

                INavRouteDrawingController& GetRouteDrawingController();
                INavRoutingServiceController& GetRoutingServiceController();
                
            private:

                INavRoutingModel* m_pNavRoutingModel;
                INavRouteDrawingController* m_pNavRouteDrawingController;
                INavRoutingServiceController* m_pNavRoutingServiceController;
                NavWidgetRouteUpdateHandler* m_pRouteUpdateHandler;
                NavWidgetRouteDrawingHandler* m_pRouteDrawingHandler;
                NavRoutingController* m_pRoutingController;

                TurnByTurn::INavTurnByTurnModel* m_pTurnByTurnModel;
                TurnByTurn::NavTurnByTurnController* m_pTurnByTurnController;
            };
        }
    }
}
