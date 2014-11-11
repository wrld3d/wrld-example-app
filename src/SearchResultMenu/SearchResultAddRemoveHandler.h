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

			void HandleSearchResultAddedMessage(const SearchResultAddedMessage& message)
			{
				const Search::SearchResultModel& model(message.Model());

        		m_menuOptions.AddItem(
					model.GetIdentifier(),
					model.GetTitle(),
					model.GetAddress(),
					model.GetCategory(),
					Eegeo_NEW(SearchResultItemModel)(
						model.GetTitle(),
						model.GetLocation().ToECEF(),
						m_menuViewModel,
						m_uiToNativeMessageBus)
				);
			}

			void HandleSearchResultRemovedMessage(const SearchResultRemovedMessage& message)
			{
				const Search::SearchResultModel& model(message.Model());
				m_menuOptions.RemoveItem(model.GetIdentifier());
			}

		public:
			SearchResultAddRemoveHandler(
				Menu::IMenuOptionsModel& menuOptions,
				Menu::IMenuViewModel& menuViewModel,
				ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
				ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_menuOptions(menuOptions)
			, m_menuViewModel(menuViewModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handleSearchResultAddedMessageBinding(this, &SearchResultAddRemoveHandler::HandleSearchResultAddedMessage)
			, m_handleSearchResultRemovedMessageBinding(this, &SearchResultAddRemoveHandler::HandleSearchResultRemovedMessage)
			{
				m_nativeToUiMessageBus.Subscribe(m_handleSearchResultAddedMessageBinding);
				m_nativeToUiMessageBus.Subscribe(m_handleSearchResultRemovedMessageBinding);
			}

			~SearchResultAddRemoveHandler()
			{
				m_nativeToUiMessageBus.Unsubscribe(m_handleSearchResultAddedMessageBinding);
				m_nativeToUiMessageBus.Unsubscribe(m_handleSearchResultRemovedMessageBinding);
			}
		};
	}
}
