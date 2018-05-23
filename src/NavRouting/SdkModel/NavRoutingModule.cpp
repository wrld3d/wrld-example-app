// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModule.h"
#include "NavRoutingModel.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"
#include "NavWidgetRouteUpdateHandler.h"
#include "NavWidgetRouteDrawingHandler.h"
#include "NavRoutingController.h"
#include "RouteService.h"
#include "NavTurnByTurnModel.h"
#include "NavTurnByTurnController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingModule::NavRoutingModule(PolyLineArgs::IShapeService& shapeService,
                                               Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                               Eegeo::Location::ILocationService& locationService,
                                               Eegeo::Location::NavigationService& navigationService,
                                               Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                               Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pNavRoutingModel = Eegeo_NEW(NavRoutingModel)();
                m_pNavRouteDrawingController = Eegeo_NEW(NavRouteDrawingController)(shapeService);
                m_pNavRoutingServiceController = Eegeo_NEW(NavRoutingServiceController)(routingWebservice);
                m_pNavRouteInstructionHelper = Eegeo_NEW(NavRouteInstructionHelper)(interiorInteractionModel);

                m_pRouteUpdateHandler = Eegeo_NEW(NavWidgetRouteUpdateHandler)(*m_pNavRoutingModel,
                                                                               *m_pNavRoutingServiceController,
                                                                               alertBoxFactory,
                                                                               *m_pNavRouteInstructionHelper);

                m_pRouteDrawingHandler = Eegeo_NEW(NavWidgetRouteDrawingHandler)(*m_pNavRoutingModel,
                                                                                 *m_pNavRouteDrawingController);

                TurnByTurn::NavTurnByTurnConfig turnByTurnConfig = TurnByTurn::NavTurnByTurnConfig();

                m_pTurnByTurnModel = Eegeo_NEW(TurnByTurn::NavTurnByTurnModel)(turnByTurnConfig,
                                                                               locationService);



                m_pTurnByTurnController = Eegeo_NEW(TurnByTurn::NavTurnByTurnController)(*m_pTurnByTurnModel,
                                                                                         *m_pNavRoutingModel,
                                                                                         navigationService);

                m_pRoutingController = Eegeo_NEW(NavRoutingController)(*m_pNavRoutingModel,
                                                                       locationService,
                                                                       *m_pTurnByTurnModel,
                                                                       messageBus);
            }

            NavRoutingModule::~NavRoutingModule()
            {
                Eegeo_DELETE m_pRoutingController;
                Eegeo_DELETE m_pTurnByTurnController;
                Eegeo_DELETE m_pTurnByTurnModel;
                Eegeo_DELETE m_pRouteDrawingHandler;
                Eegeo_DELETE m_pRouteUpdateHandler;
                Eegeo_DELETE m_pNavRouteDrawingController;
                Eegeo_DELETE m_pNavRouteInstructionHelper;
                Eegeo_DELETE m_pNavRoutingServiceController;
                Eegeo_DELETE m_pNavRoutingModel;
            }

            void NavRoutingModule::Update(float dt)
            {
                m_pTurnByTurnController->Update(dt);
            }

            INavRouteDrawingController& NavRoutingModule::GetRouteDrawingController()
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
