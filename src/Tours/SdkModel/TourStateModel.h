// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "TwitterFeed.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourStateModel
            {
            public:
                TourStateModel(const std::string& headline,
                               const std::string& description,
                               const std::string& imagePath,
                               const std::string& icon,
                               bool isTweet = false,
                               Social::TwitterFeed::TweetModel* pTweet = NULL);
                
                const std::string& Headline() const;
                
                const std::string& Description() const;
                
                const std::string& ImagePath() const;
                
                const std::string& Icon() const;
                
                bool IsTweet() const;
                
                Social::TwitterFeed::TweetModel* Tweet() const;
                
            private:
                std::string m_headline;
                std::string m_description;
                std::string m_imagePath;
                std::string m_icon;
                bool m_isTweet;
                Social::TwitterFeed::TweetModel* m_pTweet;
            };
        }
    }
}
