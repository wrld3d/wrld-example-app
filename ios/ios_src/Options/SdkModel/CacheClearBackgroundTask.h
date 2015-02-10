// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "BidirectionalBus.h"
#include "iOSHttpCache.h"
#include "WorkItem.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class CacheClearBackgroundTask : public Eegeo::Concurrency::Tasks::WorkItem, private Eegeo::NonCopyable
            {
                iOSHttpCache& m_iOSHttpCache;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
            public:
                CacheClearBackgroundTask(iOSHttpCache& iOSHttpCache,
                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_iOSHttpCache(iOSHttpCache)
                , m_messageBus(messageBus) { }
                
                void DoWork();
                
                void DoFinalizeOnMainThread();
            };
        }
    }
}
