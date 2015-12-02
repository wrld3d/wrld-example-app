// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "TwitterFeed.h"
#include <vector>

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class ITwitterFeedService
            {
            public:
                virtual ~ITwitterFeedService() { }
                
                virtual void LoadTimeline(const std::string& userId) = 0;
                
                virtual void LoadTimeLines(const std::vector<std::string>& userIds) = 0;
                
                virtual const TweetRepository& GetTweetRepositoryForUserId(std::string userId) const = 0;
                
                virtual bool ContainsTweetRepositoryForUserId(std::string userId) const = 0;
                
                virtual void AddFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback) = 0;
                
                virtual void RemoveFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback) = 0;
            };
        }
    }
}
