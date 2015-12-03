// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TwitterFeed.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class ITwitterFeedModule
            {
            public:
                virtual ~ITwitterFeedModule() { }
                
                virtual ITwitterFeedService& GetTwitterFeedService() const = 0;
            };
        }
    }
}
