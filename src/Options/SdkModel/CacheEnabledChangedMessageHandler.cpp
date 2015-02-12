// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CacheEnabledChangedMessageHandler.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            CacheEnabledChangedMessageHandler::CacheEnabledChangedMessageHandler(Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                                 ExampleAppMessaging::TMessageBus& messageBus)
            : m_networkCapabilities(networkCapabilities)
            , m_messageBus(messageBus)
            , m_messageHandlerBinding(this, &CacheEnabledChangedMessageHandler::OnPerformedCacheEnabledChange)
            {
                m_messageBus.SubscribeNative(m_messageHandlerBinding);
            }
            
            CacheEnabledChangedMessageHandler::~CacheEnabledChangedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_messageHandlerBinding);
            }
            
            void CacheEnabledChangedMessageHandler::OnPerformedCacheEnabledChange(const CacheEnabledChangedMessage& message)
            {
                // We do not expect this value to change other than via the dispatch of this message, so should always toggle.
                // If these semantics change this assert should be removed.
                Eegeo_ASSERT(message.CacheEnabled() != m_networkCapabilities.HttpCachingEnabled());
                
                m_networkCapabilities.SetHttpCachingEnabled(message.CacheEnabled());
            }
        }
    }
}
