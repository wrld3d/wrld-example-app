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
                                                                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                                           Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                                           const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                           const std::string& userId,
                                                                                           const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                                                           ExampleAppMessaging::TMessageBus& messageBus)
                    : m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_worldPinsService(worldPinsService)
                    , m_interiorController(interiorController)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_interiorSelectionModel(interiorSelectionModel)
                    , m_userId(userId)
                    , m_tweetStateDataMap(tweetStateDataMap)
                    , m_messageBus(messageBus)
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
                            
                            const float cameraRotationDelta = 15.0f;
                            
                            std::string placename = !tweet.GetPlaceName().empty() ? tweet.GetPlaceName() : tweet.GetUserName();
                            
                            Eegeo::Space::LatLong location = tweet.HasCoordinates() ? tweet.GetCoordinates() : Eegeo::Space::LatLong::FromECEF(tweetStateData->ecefTarget);
                            
                            bool isInterior = false;
                            WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData;
                            if( !tweet.HasCoordinates() )
                            {
                                isInterior = tweetStateData->isInterior;
                                worldPinInteriorData = tweetStateData->interiorData;
                            }
                            else if(tweetStateData->useBounds)
                            {
                               if(location.GetLatitude() < tweetStateData->minBounds.GetLatitude() ||
                                  location.GetLongitude() < tweetStateData->minBounds.GetLongitude() ||
                                  location.GetLatitude() > tweetStateData->maxBounds.GetLatitude() ||
                                  location.GetLongitude() > tweetStateData->maxBounds.GetLongitude())
                               {
                                   isInterior = tweetStateData->isInterior;
                                   worldPinInteriorData = tweetStateData->interiorData;
                                   location = Eegeo::Space::LatLong::FromECEF(tweetStateData->ecefTarget);
                               }
                            }
                            
                            stateMachineStates.push_back(Eegeo_NEW(TwitterFeedShowTweetState(tourModel.States()[i],
                                                                                             m_toursCameraTransitionController,
                                                                                             m_worldPinsService,
                                                                                             isInterior,
                                                                                             worldPinInteriorData,
                                                                                             m_interiorController,
                                                                                             m_interiorVisibilityUpdater,
                                                                                             m_interiorSelectionModel,
                                                                                             *tweetStateData,
                                                                                             location,
                                                                                             placename,
                                                                                             tweet.GetFirstAttachedImageUrl(),
                                                                                             tweet.GetExpandedMediaUrl(),
                                                                                             tweet.HasAttachedVideo(),
                                                                                             m_messageBus,
                                                                                             i * cameraRotationDelta)));
                        }
                        
                        return Eegeo_NEW(States::TourStateMachine)(stateMachineStates, NULL);
                    }
                }
            }
        }
    }
}