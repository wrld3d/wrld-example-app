// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "IHttpCache.h"
#include "WorkItem.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class CacheClearBackgroundTask : public Eegeo::Concurrency::Tasks::WorkItem
            {
                Eegeo::Helpers::IHttpCache& m_iOSHttpCache;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
            public:
                CacheClearBackgroundTask(Eegeo::Helpers::IHttpCache& iOSHttpCache,
                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_iOSHttpCache(iOSHttpCache)
                , m_messageBus(messageBus) { }
                
                void DoWork();
                
                void DoFinalizeOnMainThread();
            };
        }
    }
}
