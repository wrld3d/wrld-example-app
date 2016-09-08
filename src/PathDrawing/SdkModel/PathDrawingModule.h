// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IPathDrawingModule.h"
#include "IWayPointsRepository.h"
#include "WayPointsRepository.h"
#include "RouteService.h"
#include "EegeoWorld.h"
#include "IPathDrawingController.h"
#include "AppGlobeCameraWrapper.h"
#include "Types.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "BidirectionalBus.h"
#include "WorldPins.h"
#include "CategorySearch.h"
#include "WayPointOnMapModel.h"
#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class PathDrawingModule : public ExampleApp::PathDrawing::SdkModel::IPathDrawingModule, private Eegeo::NonCopyable
            {
                IWayPointsRepository* m_pWayPointsRepository;
                IPathDrawingController* m_pPathDrawingController;
                WayPointOnMapModel* m_pWayPointOnMapModel;
                
//                Eegeo::Helpers::TCallback1<PathDrawingModule, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_searchResultReceivedHandler;
                
            public:

                PathDrawingModule(WorldPins::SdkModel::IWorldPinsService& worldPinsService
                                  , Eegeo::Routes::RouteService& routeService
                                  , Eegeo::EegeoWorld& eegeoWorld
                                  , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                  , CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper
                                  , ExampleAppMessaging::TMessageBus& messageBus);

                virtual ~PathDrawingModule();

                IWayPointsRepository& GetWayPointsRepository() const;
                
                void Update(float dt);
                
//                void OnSearchQueryResponseReceivedMessage(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                
            };
        }
    }
}
