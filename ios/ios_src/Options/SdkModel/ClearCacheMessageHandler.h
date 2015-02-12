// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "iOSHttpCache.h"
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
                iOSHttpCache& m_iOSHttpCache;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Concurrency::Tasks::IWorkPool& m_workPool;
                Eegeo::Helpers::TCallback1<ClearCacheMessageHandler, const ClearCacheMessage&> m_messageHandlerBinding;
                
                void OnConfirmedCacheClear(const ClearCacheMessage& message);
                
                void DeleteCacheContents();
                
            public:
                ClearCacheMessageHandler(iOSHttpCache& iOSHttpCache,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         Eegeo::Concurrency::Tasks::IWorkPool& workPool);
                
                ~ClearCacheMessageHandler();
            };
        }
    }
}
