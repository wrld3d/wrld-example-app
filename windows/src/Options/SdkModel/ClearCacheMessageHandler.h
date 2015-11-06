// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ClearCacheMessage.h"
#include "WindowsHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class ClearCacheMessageHandler : private Eegeo::NonCopyable
            {
                Eegeo::Windows::Cache::WindowsHttpCache& m_httpCache;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<ClearCacheMessageHandler, const ClearCacheMessage&> m_messageHandlerBinding;
                
                void OnConfirmedCacheClear(const ClearCacheMessage& message);
                
                void DeleteCacheContents();
                
            public:
                ClearCacheMessageHandler(Eegeo::Windows::Cache::WindowsHttpCache& httpCache,
                                         ExampleAppMessaging::TMessageBus& messageBus);
                
                ~ClearCacheMessageHandler();
            };
        }
    }
}
