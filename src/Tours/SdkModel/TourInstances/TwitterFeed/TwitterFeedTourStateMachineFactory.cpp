// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedTourStateMachineFactory.h"

#include <vector>
#include "ITourRepository.h"
#include "TwitterFeedShowTweetState.h"
#include "TourModel.h"
#include "TourStateMachine.h"
#include "TourStateModel.h"
#include "TweetRepository.h"


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
                    TwitterFeedTourStateMachineFactory::TwitterFeedTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                                           Camera::IToursCameraController& toursCameraController,
                                                                                           ITourService& tourService,
                                                                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                                           ITourRepository& tourRepository,
                                                                                           const std::string& userId,
                                                                                           const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                                                           Metrics::IMetricsService& metricsService)
                    : m_toursCameraController(toursCameraController)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_tourService(tourService)
                    , m_worldPinsService(worldPinsService)
                    , m_tourRepository(tourRepository)
                    , m_userId(userId)
                    , m_tweetStateDataMap(tweetStateDataMap)
                    , m_metricsService(metricsService)
                    {
                        
                    }
                    
                    TwitterFeedTourStateMachineFactory::~TwitterFeedTourStateMachineFactory()
                    {
                        
                    }
                    
                    States::ITourStateMachine* TwitterFeedTourStateMachineFactory::CreateTourStateMachine(const TourModel& tourModel)
                    {
                        std::vector<States::ITourStateMachineState*> stateMachineStates;
                        std::string tourTwitterBaseUserName = tourModel.TwitterBaseUserName();
                        
                        for (int i = 0; i < tourModel.StateCount(); ++i)
                        {
                            if(!tourModel.States()[i].IsTweet())
                            {
                                Eegeo_ASSERT(false, "Non Tweet TourStateModel in twitter only factory");
                                continue;
                            }
                            
                            const Social::TwitterFeed::TweetModel& tweet = *(tourModel.States()[i].Tweet());
                            std::string nextTourName = tweet.GetUserScreenName();
                            
                            if(tweet.GetUserName() == tourTwitterBaseUserName)
                            {
                                nextTourName = "";
                            }
                            
                            const TweetStateData* tweetStateData = NULL;
                            
                            std::map<std::string, TweetStateData>::const_iterator tweetStateIt = m_tweetStateDataMap.find(tweet.GetUserScreenName());
                            
                            if(tweetStateIt == m_tweetStateDataMap.end())
                            {
                                // use the current tour's state data
                                tweetStateIt = m_tweetStateDataMap.find(m_userId);
                                
                                Eegeo_ASSERT(tweetStateIt != m_tweetStateDataMap.end(), "Couldn't find state data for tour: %s", m_userId.c_str());
                                
                                tweetStateData = &((*tweetStateIt).second);
                            }
                            else
                            {
                                // use the current state's state data
                                tweetStateData = &((*tweetStateIt).second);
                            }
                            
                            const float cameraRotationDeltaRad = Eegeo::Math::Deg2Rad(30.0f);
                            
                            std::string placename = !tweet.GetPlaceName().empty() ? tweet.GetPlaceName() : tweet.GetUserName();
                            
                            Eegeo::Space::LatLong location = tweet.HasCoordinates() ? tweet.GetCoordinates() : Eegeo::Space::LatLong::FromECEF(tweetStateData->m_ecefTarget);
                            
                            stateMachineStates.push_back(Eegeo_NEW(TwitterFeedShowTweetState(m_toursCameraTransitionController,
                                                                                             m_tourService,
                                                                                             m_worldPinsService,
                                                                                             m_tourRepository,
                                                                                             nextTourName,
                                                                                             *tweetStateData,
                                                                                             location,
                                                                                             placename,
                                                                                             tweet.GetFirstAttachedImageUrl(),
                                                                                             tweet.GetExpandedMediaUrl(),
                                                                                             tweet.HasAttachedVideo(),
                                                                                             i * cameraRotationDeltaRad)));
                        }
                        
                        return Eegeo_NEW(States::TourStateMachine)(stateMachineStates, NULL);
                    }
                }
            }
        }
    }
}