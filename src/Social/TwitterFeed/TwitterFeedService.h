// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "ITwitterFeedService.h"
#include "TwitterFeed.h"
#include "Web.h"
#include "CallbackCollection.h"
#include <queue>
#include <map>

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class TwitterFeedService : public ITwitterFeedService, public Eegeo::NonCopyable
            {
            private:
                static const std::string TwitterAuthUrl;
                static const std::string TwitterTimelineUrl;
                
                static const std::string GrantTypeKey;
                static const std::string GrantTypeValue;
                static const std::string TwitterAuthKey;
                static const std::string TwitterAuthValue;
                static const std::string ContentTypeKey;
                static const std::string ContentTypeValue;
                static const std::string RequestAuthKey;
                static const std::string RequestAuthValue;
                static const std::string AccessTokenKey;
                
                static const std::string CountParameter;
                static const std::string ScreenNameParameter;
                
                enum ServiceState
                {
                    NOT_STARTED,
                    AUTHORIZING,
                    LOADING_TIMELINE,
                    IDLE,
                    OFFLINE
                };
                
                static const int MaxTweets = 50;
                
                ServiceState m_currentServiceState;
                
                std::queue<std::string> m_accountNameQueue;
                
                std::map<std::string, TweetRepository*> m_repositoryMap;
                
                std::string m_accessToken;
                
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                
                Eegeo::Web::IWebLoadRequest* m_pCurrentAuthRequest;
                Eegeo::Web::IWebLoadRequest* m_pCurrentTimeLineRequest;
                
                Eegeo::Web::IWebLoadRequestCompletionCallback* m_pAuthCallback;
                Eegeo::Web::IWebLoadRequestCompletionCallback* m_pTimeLineCallback;
                
                Eegeo::Helpers::CallbackCollection2<const std::string&, TweetRepository&> m_feedLoadedCallbacks;
                
                void StartService();
                void LoadNextTimeLine();
                
                void HandleAuthResponse(Eegeo::Web::IWebResponse& webResponse);
                void HandleTimeLineResponse(Eegeo::Web::IWebResponse& webResponse);
                
                void ClearAccountNameQueue();
                
            public:
                TwitterFeedService(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);
                ~TwitterFeedService();
                
                void LoadTimeline(const std::string& userId);
                void LoadTimeLines(const std::vector<std::string>& userIds);
                
                bool ContainsTweetRepositoryForUserId(std::string userId) const;
                const TweetRepository& GetTweetRepositoryForUserId(std::string userId) const;
                
                void AddFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback);
                void RemoveFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback);
            };
        }
    }
}