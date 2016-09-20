// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "IHttpCache.h"
#include "Tasks.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class ClearCacheMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<Eegeo::Helpers::IHttpCache> m_httpCache;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Eegeo::Concurrency::Tasks::IWorkPool> m_workPool;
                
                Eegeo::Helpers::TCallback1<ClearCacheMessageHandler, const ClearCacheMessage&> m_messageHandlerBinding;
                
                void OnConfirmedCacheClear(const ClearCacheMessage& message);
                
                void DeleteCacheContents();
                
            public:
                ClearCacheMessageHandler(const std::shared_ptr<Eegeo::Helpers::IHttpCache>& httpCache,
                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                         const std::shared_ptr<Eegeo::Concurrency::Tasks::IWorkPool>& workPool);
                
                ~ClearCacheMessageHandler();
            };
        }
    }
}
