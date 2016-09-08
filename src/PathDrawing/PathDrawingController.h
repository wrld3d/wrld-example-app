// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "RouteService.h"
#include "IWayPointsRepository.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "EegeoWorld.h"
#include "IPathDrawingController.h"
#include "AppGlobeCameraWrapper.h"
#include "IWayPointsRepository.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        class PathDrawingController : public IPathDrawingController
        {
        private:
            PathDrawing::SdkModel::IWayPointsRepository& m_pWayPointsRepository;
            Eegeo::Routes::RouteService& m_routeService;
            Eegeo::EegeoWorld& m_world;
            AppCamera::SdkModel::AppGlobeCameraWrapper& m_cameraWrapper;
            ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Helpers::TCallback1<PathDrawingController, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_searchResultReceivedHandler;
            
            bool m_createdRoutes;
            std::vector<Eegeo::Routes::Route*> m_routes;
            Eegeo::Routes::Style::Thickness::LinearAltitudeBasedRouteThicknessPolicy m_routeThicknessPolicy;
            
            void CreateRoutePlan();
            
            void RemoveRoutePlan();
            
            void OnSearchQueryResponseReceivedMessage(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
            
        public:
            PathDrawingController(Eegeo::Routes::RouteService& routeService
                                  , Eegeo::EegeoWorld& eegeoWorld
                                  , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                  , PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository
                                  , ExampleAppMessaging::TMessageBus& messageBus);
            
            void Start() {}
            virtual void Update(float dt);
            void Draw() {}
            void Suspend();
            
            virtual ~PathDrawingController();
            
        };
    }
}
