// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "TweetStateData.h"

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
                    class ITwitterFeedTourModule
                    {
                    public:
                        virtual ~ITwitterFeedTourModule() { }
                        
                        virtual const std::map<std::string, TweetStateData>& GetTweetStateDataMap() const = 0;
                    };
                }
            }
        }
    }
}