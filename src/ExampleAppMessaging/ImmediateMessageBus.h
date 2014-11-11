// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "ICallback.h"
#include "CatalogBinding.h"

namespace ExampleApp
{
    namespace ExampleAppMessaging
    {
		template <typename TMessageCatalog>
		class ImmediateMessageBus : private Eegeo::NonCopyable
		{
		private:
			TMessageCatalog m_catalog;

		public:
			template <typename TMessage>
			void Publish(const TMessage& message)
			{
				CatalogBinding<TMessage>& binding(m_catalog);
				binding.Dispatch(message);
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

			void Flush() { }
		};
    }
}

