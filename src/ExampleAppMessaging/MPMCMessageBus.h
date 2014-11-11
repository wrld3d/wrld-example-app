// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "ICallback.h"
#include "MPMCQueue.h"
#include "CatalogBinding.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
		template <typename TMessageCatalog>
		class MPMCMessageBus : private Eegeo::NonCopyable
		{
		private:
			TMessageCatalog m_catalog;

			class MessageInfo
			{
			public:
				virtual ~MessageInfo() {};
				virtual void Dispatch() = 0;
			};

			template <typename TMessage>
			class TypedMessageInfo : public MessageInfo
			{
			private:
				TMessage m_message;
				TMessageCatalog& m_catalog;
			public:
				TypedMessageInfo(const TMessage& message,
								 TMessageCatalog& catalog)
				: m_message(message)
				, m_catalog(catalog)
				{
				}

				void Dispatch()
				{
					CatalogBinding<TMessage>& binding(m_catalog);
					binding.Dispatch(m_message);
				}
			};

			Eegeo::Concurrency::MPMCQueue<MessageInfo*> m_messages;

		public:
			template <typename TMessage>
			void Publish(const TMessage& message)
			{
				m_messages.Enqueue(new TypedMessageInfo<TMessage>(message, m_catalog));
			}

			template <typename TMessage>
			void Subscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
			{
				CatalogBinding<TMessage>& binding(m_catalog);
				binding.Subscribe(handler);
			}

			template <typename TMessage>
			void Unsubscribe(Eegeo::Helpers::ICallback1<const TMessage&>& handler)
			{
				CatalogBinding<TMessage>& binding(m_catalog);
				binding.Unsubscribe(handler);
			}

			void Flush()
			{
				MessageInfo* pMessage(NULL);

				while(m_messages.TryDequeue(pMessage))
				{
					pMessage->Dispatch();
					delete pMessage;
				}
			}
		};
    }
}

