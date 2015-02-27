// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "MessageQueue.h"
#include "DispatchQueue.h"
#include "SdkDomainEventsMessageCatalog.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        template <typename TSdkModelDomainEventsMessageCatalog>
        class SdkModelDomainEventBus : private Eegeo::NonCopyable
        {
        private:
            DispatchQueue<TSdkModelDomainEventsMessageCatalog> m_messageDispatcher;
            
        public:
            
            template <typename TMessage>
            void Publish(const TMessage& message)
            {
                m_messageDispatcher.TryEnqueue(message);
                m_messageDispatcher.Flush();
            }
            
            template <typename TMessage>
            void Subscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_messageDispatcher.Subscribe(handler);
            }
            
            template <typename TMessage>
            void Unsubscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_messageDispatcher.Unsubscribe(handler);
            }
        };
        
        typedef SdkModelDomainEventBus<SdkDomainEventsMessageCatalog> TSdkModelDomainEventBus;
    }
}