// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedModule.h"
#include "TweetRepository.h"
#include "TwitterFeedService.h"
#include "IWebLoadRequestFactory.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            TwitterFeedModule::TwitterFeedModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void TwitterFeedModule::Register()
            {
                m_builder->registerType<TwitterFeedService>().as<ITwitterFeedService>().singleInstance();
            }
        }
    }
}
