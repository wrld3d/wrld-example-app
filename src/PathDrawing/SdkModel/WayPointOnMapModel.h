// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "ICallback.h"
#include "WayPointModel.h"
#include "WayPointType.h"
#include "Space.h"
#include "Types.h"
#include "WorldPins.h"
#include "TagSearch.h"
#include "IWayPointsRepository.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class WayPointOnMapModel : private Eegeo::NonCopyable
            {
            private:
                Eegeo::Helpers::TCallback1<WayPointOnMapModel, WayPointModel*> m_onWayPointAddedCallBack;
                Eegeo::Helpers::TCallback1<WayPointOnMapModel, WayPointModel*> m_onWayPointRemovedCallBack;
                PathDrawing::SdkModel::IWayPointsRepository& m_wayPointsRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                void OnWayPointAdded(WayPointModel*& wayPoint);
                void AddWayPointView(WayPointModel*& wayPoint);
                
                void OnWayPointRemoved(WayPointModel*& wayPoint);
                void RemoveWayPointView(WayPointModel*& wayPoint);
                
                typedef std::map<ExampleApp::PathDrawing::WayPointModel*, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*>::iterator mapIt;
                
                std::map<ExampleApp::PathDrawing::WayPointModel*, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*> m_wayPointsToPinModel;
                
                public:
                
                virtual ~WayPointOnMapModel();
                
                WayPointOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                   TagSearch::ISearchResultIconKeyMapper& searchResultIconCategoryMapper,
                                   PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository,
                                   ExampleAppMessaging::TMessageBus& messageBus);
                
                
                
                std::string GetWayPointIconForType(const ExampleApp::PathDrawing::WayPointType::Values type);
                
            };
        }
    }
}
