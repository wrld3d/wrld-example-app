// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "IMenuOptionsModel.h"
#include "SearchResultModel.h"
#include "SearchResultItemModel.h"
#include "IMenuViewModel.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultAddRemoveHandler : private Eegeo::NonCopyable
		{
			Menu::IMenuOptionsModel& m_menuOptions;
			Menu::IMenuViewModel& m_menuViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;

			Eegeo::Helpers::TCallback1<SearchResultAddRemoveHandler, const SearchResultAddedMessage&> m_handleSearchResultAddedMessageBinding;
			Eegeo::Helpers::TCallback1<SearchResultAddRemoveHandler, const SearchResultRemovedMessage&> m_handleSearchResultRemovedMessageBinding;

			void HandleSearchResultAddedMessage(const SearchResultAddedMessage& message);

			void HandleSearchResultRemovedMessage(const SearchResultRemovedMessage& message);

		public:
			SearchResultAddRemoveHandler(
			    Menu::IMenuOptionsModel& menuOptions,
			    Menu::IMenuViewModel& menuViewModel,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~SearchResultAddRemoveHandler();
		};
	}
}
