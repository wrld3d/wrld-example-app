// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "CacheEnabledChangedMessage.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class CacheEnabledChangedMessageHandler : private Eegeo::NonCopyable
            {
                Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<CacheEnabledChangedMessageHandler, const CacheEnabledChangedMessage&> m_messageHandlerBinding;
                
                void OnPerformedCacheEnabledChange(const CacheEnabledChangedMessage& message);
                
            public:
                CacheEnabledChangedMessageHandler(Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                
                ~CacheEnabledChangedMessageHandler();
            };
        }
    }
}
