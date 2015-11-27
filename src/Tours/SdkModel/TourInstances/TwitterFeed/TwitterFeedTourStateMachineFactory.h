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
                        ITourService& m_tourService;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        ITourRepository& m_tourRepository;
                        std::string m_userId;
                        Metrics::IMetricsService& m_metricsService;
                        
                        const std::map<std::string, TweetStateData>& m_tweetStateDataMap;
                    public:
                        TwitterFeedTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                           Camera::IToursCameraController& toursCameraController,
                                                           ITourService& tourService,
                                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                           ITourRepository& tourRepository,
                                                           const std::string& userId,
                                                           const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                           Metrics::IMetricsService& metricsService);
                        ~TwitterFeedTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                    };
                }
            }
        }
    }
}