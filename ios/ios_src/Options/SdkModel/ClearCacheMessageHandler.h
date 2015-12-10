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
                Eegeo::Helpers::IHttpCache& m_iOSHttpCache;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Concurrency::Tasks::IWorkPool& m_workPool;
                Eegeo::Helpers::TCallback1<ClearCacheMessageHandler, const ClearCacheMessage&> m_messageHandlerBinding;
                
                void OnConfirmedCacheClear(const ClearCacheMessage& message);
                
                void DeleteCacheContents();
                
            public:
                ClearCacheMessageHandler(Eegeo::Helpers::IHttpCache& iOSHttpCache,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         Eegeo::Concurrency::Tasks::IWorkPool& workPool);
                
                ~ClearCacheMessageHandler();
            };
        }
    }
}
