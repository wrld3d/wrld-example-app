// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CatalogBinding.h"
#include "MessageQueue.h"
#include "NativeToUiMessageCatalog.h"
#include "UiToNativeMessageCatalog.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
        struct TBusCatalogs
        {
            typedef ExampleAppMessaging::NativeToUiMessageCatalog TDispatchToUiMessageCatalog;
            typedef ExampleAppMessaging::UiToNativeMessageCatalog TDispatchToNativeMessageCatalog;
        };

        template <typename TBusCatalogs>
        class BidirectionalBus : private Eegeo::NonCopyable
        {
        private:
            typedef typename TBusCatalogs::TDispatchToNativeMessageCatalog TDispatchToNativeMessageCatalog;
            typedef typename TBusCatalogs::TDispatchToUiMessageCatalog TDispatchToUiMessageCatalog;

            class MessageInfo
            {
            public:
                virtual ~MessageInfo() {};
                virtual void Dispatch() = 0;
            };

            template <typename TMessageCatalog>
            class DispatchQueue
            {
            private:
                template <typename TMessage>
                class TypedMessageInfo : public MessageInfo
                {
                private:
                    TMessage m_message;
                    TMessageCatalog& m_catalog;
                public:
                    TypedMessageInfo(const TMessage& message, TMessageCatalog& catalog)
                        : m_message(message)
                        , m_catalog(catalog)
                    {
                    }

                    void Dispatch()
                    {
                        Eegeo::Messaging::CatalogBinding<TMessage>& binding(m_catalog);
                        binding.Dispatch(m_message);
                    }
                };

                template<typename TMessage>
                struct HandlesMessage
                {
                    typedef char (&NotHandled)[1];
                    typedef char (&Handled)[2];
                    static Handled CheckImplements(Eegeo::Messaging::CatalogBinding<TMessage>*);
                    static NotHandled CheckImplements(...);
                    static const bool IsHandled = sizeof(CheckImplements(static_cast<TMessageCatalog*>(0))) == sizeof(Handled);
                };

                template<bool Condition, typename ReturnType = void>
                struct Conditional
                {
                    typedef ReturnType rt;
                };

                template<typename ReturnType>
                struct Conditional<false, ReturnType> { };

                template<typename TMessage>
                typename Conditional<HandlesMessage<TMessage>::IsHandled>::rt EnqueueIfHandled(const TMessage& message)
                {
                    // message is handled by this catalog...
                    m_messages.Enqueue(new TypedMessageInfo<TMessage>(message, m_catalog));
                }

                template<typename TMessage>
                typename Conditional<!HandlesMessage<TMessage>::IsHandled>::rt EnqueueIfHandled(const TMessage& message)
                {
                    // message is not handled by this catalog...
                }

                TMessageCatalog m_catalog;
                Eegeo::Messaging::MessageQueue<MessageInfo*> m_messages;

            public:

                template <typename TMessage>
                void TryEnqueue(const TMessage& message)
                {
                    EnqueueIfHandled(message);
                }

                template <typename TMessage>
                void Subscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
                {
                    Eegeo::Messaging::CatalogBinding<TMessage>& binding(m_catalog);
                    binding.Subscribe(handler);
                }

                template <typename TMessage>
                void Unsubscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
                {
                    Eegeo::Messaging::CatalogBinding<TMessage>& binding(m_catalog);
                    binding.Unsubscribe(handler);
                }

                void Flush()
                {
                    MessageInfo* info;
                    while (m_messages.TryDequeue(info))
                    {
                        info->Dispatch();
                        delete info;
                    }
                }
            };

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

        typedef BidirectionalBus<TBusCatalogs> TMessageBus;
    }
}