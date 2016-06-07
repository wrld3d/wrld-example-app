// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedTourObserver.h"
#include "TourStateModel.h"
#include "TourModel.h"
#include "TwitterFeedTourStateMachineFactory.h"
#include "ITourService.h"
#include "ITourRepository.h"
#include "ITwitterFeedService.h"
#include <vector>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

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
                    TwitterFeedTourObserver::TwitterFeedTourObserver(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                     ITourService& tourService,
                                                                     WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                     InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     ITourRepository& tourRepository,
                                                                     Social::TwitterFeed::ITwitterFeedService& twitterFeedService,
                                                                     const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                                     const std::map<std::string, std::string>& twitterTourIconOverrideMap,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                    : m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_tourService(tourService)
                    , m_worldPinsService(worldPinsService)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorSelectionModel(interiorSelectionModel)
                    , m_tourRepository(tourRepository)
                    , m_twitterFeedService(twitterFeedService)
                    , m_twitterFeedLoadedCallback(this, &TwitterFeedTourObserver::OnTwitterFeedLoaded)
                    , m_tweetStateDataMap(tweetStateDataMap)
                    , m_twitterTourIconOverrideMap(twitterTourIconOverrideMap)
                    , m_messageBus(messageBus)
                    {
                        m_twitterFeedService.AddFeedLoadedCallback(m_twitterFeedLoadedCallback);
                    }
                    
                    TwitterFeedTourObserver::~TwitterFeedTourObserver()
                    {
                        m_twitterFeedService.RemoveFeedLoadedCallback(m_twitterFeedLoadedCallback);
                    }
                    
                    void TwitterFeedTourObserver::OnTwitterFeedLoaded(const std::string& userId,
                                                                      Social::TwitterFeed::TweetRepository& tweetRepository)
                    {
                        std::vector<Social::TwitterFeed::TweetModel*> tweets;
                        
                        if(tweetRepository.GetItemCount() == 0)
                        {
                            Eegeo_TTY("No tweets found for %s", userId.c_str());
                            return;
                        }
                        
                        for(int i = 0; i < tweetRepository.GetItemCount(); ++i)
                        {
                            tweets.push_back(tweetRepository.GetItemAtIndex(i));
                        }
                        
                        std::map<std::string, TweetStateData>::const_iterator tweetStateIt = m_tweetStateDataMap.find(userId);
                        
                        Eegeo_ASSERT(tweetStateIt != m_tweetStateDataMap.end(), "Couldn't find tweet state data for account: %s", userId.c_str());
                        
                        TweetStateData tweetStateData = (*tweetStateIt).second;
                        
                        Eegeo::Space::LatLong tourLocation = Eegeo::Space::LatLong::FromECEF(tweetStateData.ecefTarget);
                        
                        rapidjson::Document jsonDocument;
                        jsonDocument.SetObject();
                        
                        rapidjson::Document::AllocatorType& allocator = jsonDocument.GetAllocator();

                        rapidjson::Value userIdValue(userId.c_str(), allocator);
                        rapidjson::Value imageUrlValue(tweetRepository.GetItemAtIndex(0)->GetBaseProfileImageUrl().c_str(), allocator);
                        
                        jsonDocument.AddMember("screenName", userIdValue, allocator);
                        jsonDocument.AddMember("imageUrl", imageUrlValue, allocator);
                        
                        rapidjson::StringBuffer buffer;
                        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                        jsonDocument.Accept(writer);
                        
                        std::string tourName = tweetRepository.GetItemAtIndex(0)->GetBaseUserName();
                        std::string twitterBaseUserName = tweetRepository.GetItemAtIndex(0)->GetBaseUserName();
                        const std::string twitterBaseProfileImage = tweetRepository.GetItemAtIndex(0)->GetBaseProfileImageThumbUrl();
                        
                        std::vector<TourStateModel> states;
                        for(int i = 0; i < tweets.size(); ++i)
                        {
                            states.push_back(TourStateModel(tweets[i]->GetUserName() + " (@"+tweets[i]->GetUserScreenName()+")",
                                                            tweets[i]->GetText(),
                                                            "",
                                                            "tours",
                                                            true,
                                                            tweets[i]));
                        }
                        
                        
                        const bool isInterior = tweetStateData.isInterior;
                        ExampleApp::WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData = tweetStateData.interiorData;
                        
                        const std::string& pinIconKey = PinIconKeyForTwitterUser(userId);

                        
                        ExampleApp::Tours::SdkModel::TourModel tourModel(tourName,
                                                                         "@"+userId,
                                                                         pinIconKey,
                                                                         tourLocation,
                                                                         tweetStateData.visibleOnMap,
                                                                         isInterior,
                                                                         worldPinInteriorData,
                                                                         false,
                                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                                         Helpers::ColorHelpers::Color::FromRGB(255, 255, 255),
                                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                                         Helpers::ColorHelpers::Color::FromRGB(30, 123, 195),
                                                                         states,
                                                                         true,
                                                                         twitterBaseUserName,
                                                                         twitterBaseProfileImage);
                        
                        TwitterFeedTourStateMachineFactory factory(m_toursCameraTransitionController,
                                                                   m_worldPinsService,
                                                                   m_interiorVisibilityUpdater,
                                                                   m_interiorInteractionModel,
                                                                   m_interiorSelectionModel,
                                                                   userId,
                                                                   m_tweetStateDataMap,
                                                                   m_messageBus);
                        
                        m_tourService.AddTour(tourModel, *factory.CreateTourStateMachine(tourModel));
                        
                        // Assumes tours never removed
                        m_setOfTourTwitterBaseUserNames.insert(twitterBaseUserName);
                        
                        UpadateTweetLinksOut();
                    }
                    
                    std::string TwitterFeedTourObserver::PinIconKeyForTwitterUser(const std::string twitterUserId) const
                    {
                        if(m_twitterTourIconOverrideMap.find(twitterUserId) != m_twitterTourIconOverrideMap.end())
                        {
                            return m_twitterTourIconOverrideMap.at(twitterUserId);
                        }
                        else
                        {
                            return "feed_twitter";
                        }
                    }
                    
                    void TwitterFeedTourObserver::UpadateTweetLinksOut()
                    {
                        int tourCount = static_cast<int>(m_tourRepository.GetItemCount());
                        
                        for(int i = 0; i < tourCount; ++i)
                        {
                            TourModel tourModel = m_tourRepository.GetItemAtIndex(i);
                            
                            if(!tourModel.UsesTwitter())
                            {
                                continue;
                            }
                            
                            const std::vector<TourStateModel>& states = tourModel.States();
                            
                            for(int stateIndex = 0; stateIndex < states.size(); ++stateIndex)
                            {
                                const TourStateModel& tourStateModel = states[stateIndex];
                                if(!tourStateModel.IsTweet())
                                {
                                    continue;
                                }
                                const std::string& userName = tourStateModel.Tweet()->GetUserName();
                                if(userName != tourModel.TwitterBaseUserName() &&
                                   m_setOfTourTwitterBaseUserNames.find(userName) != m_setOfTourTwitterBaseUserNames.end())
                                {
                                    tourStateModel.Tweet()->SetDoesLinkOut(true);
                                }
                            }
                        }

                    }
                    
                }
            }
        }
    }
}
