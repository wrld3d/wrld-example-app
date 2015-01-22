// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		class CategorySearchSelectedMessageHandler : private Eegeo::NonCopyable
		{
			Search::ISearchQueryPerformer& m_searchQueryPerformer;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<CategorySearchSelectedMessageHandler, const CategorySearchSelectedMessage&> m_handlerBinding;

			void HandleReceivedCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message);

		public:
			CategorySearchSelectedMessageHandler(
			    Search::ISearchQueryPerformer& searchQueryPerformer,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~CategorySearchSelectedMessageHandler();
		};
	}
}
