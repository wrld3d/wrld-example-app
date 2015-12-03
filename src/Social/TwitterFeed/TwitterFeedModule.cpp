// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedModule.h"
#include "TweetRepository.h"
#include "TwitterFeedService.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            TwitterFeedModule::TwitterFeedModule(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            : m_pTwitterFeedService(NULL)
            {
                m_pTwitterFeedService = Eegeo_NEW(TwitterFeedService)(webLoadRequestFactory);
            }
            
            TwitterFeedModule::~TwitterFeedModule()
            {
                Eegeo_DELETE m_pTwitterFeedService;
            }
            
            ITwitterFeedService& TwitterFeedModule::GetTwitterFeedService() const
            {
                return *m_pTwitterFeedService;
            }
        }
    }
}
