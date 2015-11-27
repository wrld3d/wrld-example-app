// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITwitterFeedModule.h"
#include "TwitterFeed.h"
#include "Web.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class TwitterFeedModule : public ITwitterFeedModule, public Eegeo::NonCopyable
            {
            private:
                ITwitterFeedService* m_pTwitterFeedService;
            public:
                TwitterFeedModule(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);
                ~TwitterFeedModule();
                
                ITwitterFeedService& GetTwitterFeedService() const;
            };
        }
    }
}