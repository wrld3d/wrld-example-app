// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DebugRenderer.h"
#include "AlertBox.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "NavRouting.h"
#include "Routes.h"
#include "Location.h"
#include "InteriorsModelRepository.h"
#include "CameraTransitions.h"
#include "Compass.h"
#include "Markers.h"
#include "WorldPins.h"

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
                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                 Compass::SdkModel::ICompassModel& compassModel,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                 Eegeo::Markers::IMarkerService& markerService,
                                 WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                 Eegeo::DebugRendering::DebugRenderer& debugRenderer);

                ~NavRoutingModule();

                void Update(float dt);

                INavRouteDrawingController& GetRouteDrawingController();
                INavRoutingServiceController& GetRoutingServiceController();
                TurnByTurn::NavTurnByTurnLocationService& GetTurnByTurnLocationService();
                
            private:

                INavRoutingModel* m_pNavRoutingModel;
                INavRoutingPolylineFactory* m_pNavRoutingPolylineFactory;
                INavRouteDrawingController* m_pNavRouteDrawingController;
                INavRoutingServiceController* m_pNavRoutingServiceController;
                NavWidgetRouteUpdateHandler* m_pRouteUpdateHandler;
                NavWidgetRouteDrawingHandler* m_pRouteDrawingHandler;
                NavRoutingController* m_pRoutingController;
                NavRoutingCameraController* m_pRoutingCameraController;

                TurnByTurn::INavTurnByTurnModel* m_pTurnByTurnModel;
                TurnByTurn::NavTurnByTurnController* m_pTurnByTurnController;
                TurnByTurn::NavTurnByTurnLocationService* m_pTurnByTurnLocationService;
            };
        }
    }
}
