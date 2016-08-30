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
                const std::shared_ptr<Net::SdkModel::INetworkCapabilities> m_networkCapabilities;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<CacheEnabledChangedMessageHandler, const CacheEnabledChangedMessage&> m_messageHandlerBinding;
                
                void OnPerformedCacheEnabledChange(const CacheEnabledChangedMessage& message);
                
            public:
                CacheEnabledChangedMessageHandler(const std::shared_ptr<Net::SdkModel::INetworkCapabilities>& networkCapabilities,
                                                  const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~CacheEnabledChangedMessageHandler();
            };
        }
    }
}
