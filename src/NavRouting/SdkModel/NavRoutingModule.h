// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AlertBox.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "NavRouting.h"
#include "Routes.h"
#include "Location.h"
#include "InteriorsModelRepository.h"
#include "Markers.h"
#include "CameraTransitions.h"
#include "Compass.h"
#include "WorldPins.h"
#include "GpsMarker.h"
#include "Menu.h"
#include "NavRoutingLocationFinder.h"
#include "WorldPins.h"
#include "NavRoutingWorldPinsVisibilityHandler.h"
#include "AppCamera.h"
#include "MapCamera.h"
#include "Search.h"
#include "IHighlightColorMapper.h"

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
                                 Eegeo::Camera::MapCamera::MapCameraDistanceFromBoundsCalculator& cameraDistanceFromBoundsCalculator,
                                 Compass::SdkModel::ICompassModel& compassModel,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                 Eegeo::Markers::IMarkerService& markerService,
                                 WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                 GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                 WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController,
                                 AppCamera::SdkModel::IAppCameraLocationPicker& locationPicker,
                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                 const InteriorsExplorer::SdkModel::Highlights::IHighlightColorMapper& highlightColorMapper,
                                 Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService);

                ~NavRoutingModule();

                void Update(float dt);

                INavRouteDrawingController& GetRouteDrawingController();
                INavRoutingServiceController& GetRoutingServiceController();
                INavRoutingCustomLocationPicker& GetCustomLocationPicker();

                Menu::View::IMenuModel& GetNavMenuModel() const;
                
            private:

                INavRoutingModel* m_pNavRoutingModel;
                INavRoutingPolylineFactory* m_pNavRoutingPolylineFactory;
                INavRouteDrawingController* m_pNavRouteDrawingController;
                INavRoutingServiceController* m_pNavRoutingServiceController;
                NavWidgetRouteUpdateHandler* m_pRouteUpdateHandler;
                NavWidgetRouteDrawingHandler* m_pRouteDrawingHandler;
                NavRoutingLocationFinder* m_pNavRoutingLocationFinder;
                INavRoutingCustomLocationPicker* m_pNavRoutingCustomLocationPicker;
                INavRoutingHighlightsController* m_pNavRoutingHighlightsController;
                NavRoutingController* m_pRoutingController;
                NavRoutingCameraController* m_pRoutingCameraController;
                NavRoutingWorldPinsVisibilityHandler* m_pRoutingWorldPinsVisibilityHandler;
                
                TurnByTurn::INavTurnByTurnModel* m_pTurnByTurnModel;
                TurnByTurn::NavTurnByTurnController* m_pTurnByTurnController;
                TurnByTurn::NavTurnByTurnCompletionHandler* m_pTurnByTurnCompletionHandler;

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
            };
        }
    }
}
