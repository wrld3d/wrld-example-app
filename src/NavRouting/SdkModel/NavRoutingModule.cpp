// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModule.h"
#include "NavRoutingModel.h"
#include "NavRoutingPolylineFactory.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"
#include "NavWidgetRouteUpdateHandler.h"
#include "NavWidgetRouteDrawingHandler.h"
#include "NavRoutingController.h"
#include "RouteService.h"
#include "NavTurnByTurnModel.h"
#include "NavTurnByTurnController.h"
#include "NavRoutingCameraController.h"

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
                                                CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                Compass::SdkModel::ICompassModel& compassModel,
                                                ExampleAppMessaging::TMessageBus& messageBus,
                                                Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                Eegeo::Markers::IMarkerService& markerService,
                                                WorldPins::SdkModel::IWorldPinsService& worldPinsService)
            {
                m_pNavRoutingModel = Eegeo_NEW(NavRoutingModel)();
                
                NavRoutingPolylineConfig polylineConfig = NavRoutingPolylineConfig();
                m_pNavRoutingPolylineFactory = Eegeo_NEW(NavRoutingPolylineFactory)(shapeService,
                                                                                    polylineConfig);
                
                m_pNavRouteDrawingController = Eegeo_NEW(NavRouteDrawingController)(*m_pNavRoutingModel,
                                                                                    *m_pNavRoutingPolylineFactory,
                                                                                    shapeService,
                                                                                    markerService);
                
                m_pNavRoutingServiceController = Eegeo_NEW(NavRoutingServiceController)(routingWebservice);

                m_pRouteUpdateHandler = Eegeo_NEW(NavWidgetRouteUpdateHandler)(*m_pNavRoutingModel,
                                                                               *m_pNavRoutingServiceController,
                                                                               alertBoxFactory);

                TurnByTurn::NavTurnByTurnConfig turnByTurnConfig = TurnByTurn::NavTurnByTurnConfig();

                m_pTurnByTurnModel = Eegeo_NEW(TurnByTurn::NavTurnByTurnModel)(turnByTurnConfig,
                                                                               locationService);



                m_pTurnByTurnController = Eegeo_NEW(TurnByTurn::NavTurnByTurnController)(*m_pTurnByTurnModel,
                                                                                         *m_pNavRoutingModel,
                                                                                         navigationService);
                
                m_pRouteDrawingHandler = Eegeo_NEW(NavWidgetRouteDrawingHandler)(*m_pNavRoutingModel,
                                                                                 *m_pTurnByTurnModel,
                                                                                 *m_pNavRouteDrawingController);

                m_pRoutingController = Eegeo_NEW(NavRoutingController)(*m_pNavRoutingModel,
                                                                       locationService,
                                                                       *m_pTurnByTurnModel,
                                                                       messageBus,
                                                                       interiorsModelRepository,
                                                                       alertBoxFactory,
                                                                       worldPinsService);
                
                m_pRoutingCameraController = Eegeo_NEW(NavRoutingCameraController)(*m_pNavRoutingModel,
                                                                                   cameraTransitionController,
                                                                                   navigationService,
                                                                                   compassModel);
            }

            NavRoutingModule::~NavRoutingModule()
            {
                Eegeo_DELETE m_pRoutingCameraController;
                Eegeo_DELETE m_pRoutingController;
                Eegeo_DELETE m_pRouteDrawingHandler;
                Eegeo_DELETE m_pTurnByTurnController;
                Eegeo_DELETE m_pTurnByTurnModel;
                Eegeo_DELETE m_pRouteUpdateHandler;
                Eegeo_DELETE m_pNavRoutingServiceController;
                Eegeo_DELETE m_pNavRouteDrawingController;
                Eegeo_DELETE m_pNavRoutingPolylineFactory;
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
