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
#include "Metrics.h"
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
                        Camera::IToursCameraController& m_toursCameraController;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        std::string m_userId;
                        Metrics::IMetricsService& m_metricsService;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        const std::map<std::string, TweetStateData>& m_tweetStateDataMap;
                    public:
                        TwitterFeedTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                           Camera::IToursCameraController& toursCameraController,
                                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                           Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                           const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           const std::string& userId,
                                                           const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                           Metrics::IMetricsService& metricsService,
                                                           ExampleAppMessaging::TMessageBus& messageBus);
                        ~TwitterFeedTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                    };
                }
            }
        }
    }
}