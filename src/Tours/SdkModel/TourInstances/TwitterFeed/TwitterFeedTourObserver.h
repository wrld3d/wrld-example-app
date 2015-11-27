// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "types.h"
#include "TweetRepository.h"
#include "Tours.h"
#include "WorldPins.h"
#include "TwitterFeed.h"
#include <map>
#include <TweetStateData.h>
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
                    class TwitterFeedTourObserver : private Eegeo::NonCopyable
                    {
                    private:
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::IToursCameraController& m_toursCameraController;
                        ITourService& m_tourService;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        ITourRepository& m_tourRepository;
                        Social::TwitterFeed::ITwitterFeedService& m_twitterFeedService;
                        Metrics::IMetricsService& m_metricsService;
                        
                        const std::map<std::string, TweetStateData>& m_tweetStateDataMap;
                        
                        Eegeo::Helpers::TCallback2<TwitterFeedTourObserver, const std::string&, Social::TwitterFeed::TweetRepository&> m_twitterFeedLoadedCallback;
                        
                        void OnTwitterFeedLoaded(const std::string& userId,
                                                 Social::TwitterFeed::TweetRepository& tweetRepository);
                        
                        void UpadateTweetLinksOut();
                    public:
                        TwitterFeedTourObserver(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                Camera::IToursCameraController& toursCameraController,
                                                ITourService& tourService,
                                                WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                ITourRepository& tourRepository,
                                                Social::TwitterFeed::ITwitterFeedService& twitterFeedService,
                                                const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                Metrics::IMetricsService& metricsService);
                        ~TwitterFeedTourObserver();
                    };
                }
            }
        }
    }
}
