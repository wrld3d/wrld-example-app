// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "MessageQueue.h"
#include "DispatchQueue.h"
#include "NativeToUiMessageCatalog.h"
#include "UiToNativeMessageCatalog.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        struct TDefaultBusCatalogs
        {
            typedef ExampleAppMessaging::NativeToUiMessageCatalog TDispatchToUiMessageCatalog;
            typedef ExampleAppMessaging::UiToNativeMessageCatalog TDispatchToNativeMessageCatalog;
        };

        template <typename TBusCatalogs = TDefaultBusCatalogs>
        class BidirectionalBus : private Eegeo::NonCopyable
        {
        private:
            typedef typename TBusCatalogs::TDispatchToNativeMessageCatalog TDispatchToNativeMessageCatalog;
            typedef typename TBusCatalogs::TDispatchToUiMessageCatalog TDispatchToUiMessageCatalog;

            DispatchQueue<TDispatchToUiMessageCatalog> m_dispatchToUiQueue;
            DispatchQueue<TDispatchToNativeMessageCatalog> m_dispatchToNativeQueue;

        public:

            template <typename TMessage>
            void Publish(const TMessage& message)
            {
                m_dispatchToUiQueue.TryEnqueue(message);
                m_dispatchToNativeQueue.TryEnqueue(message);
#ifndef EEGEO_DROID
                m_dispatchToUiQueue.Flush();
                m_dispatchToNativeQueue.Flush();
#endif
            }

            template <typename TMessage>
            void SubscribeUi(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_dispatchToUiQueue.Subscribe(handler);
            }

            template <typename TMessage>
            void UnsubscribeUi(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_dispatchToUiQueue.Unsubscribe(handler);
            }

            template <typename TMessage>
            void SubscribeNative(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_dispatchToNativeQueue.Subscribe(handler);
            }

            template <typename TMessage>
            void UnsubscribeNative(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
            {
                m_dispatchToNativeQueue.Unsubscribe(handler);
            }

            void FlushToUi()
            {
#ifdef EEGEO_DROID
                m_dispatchToUiQueue.Flush();
#endif
            }

            void FlushToNative()
            {
#ifdef EEGEO_DROID
                m_dispatchToNativeQueue.Flush();
#endif
            }
        };

        typedef BidirectionalBus<> TMessageBus;
    }
}