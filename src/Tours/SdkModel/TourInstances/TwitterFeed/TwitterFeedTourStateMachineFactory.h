// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "WorldPins.h"
#include <string>
#include "TwitterFeed.h"
#include <map>
#include "TweetStateData.h"
#include "LatLongAltitude.h"
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    class TwitterFeedTourStateMachineFactory : private Eegeo::NonCopyable
                    {
                    private:
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        std::string m_userId;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        const std::map<std::string, TweetStateData>& m_tweetStateDataMap;
                    public:
                        TwitterFeedTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                           Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           const std::string& userId,
                                                           const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                           ExampleAppMessaging::TMessageBus& messageBus);
                        ~TwitterFeedTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                    };
                }
            }
        }
    }
}