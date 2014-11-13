// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultAddRemoveHandler.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultAddRemoveHandler::SearchResultAddRemoveHandler(
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

		SearchResultAddRemoveHandler::~SearchResultAddRemoveHandler()
		{
			m_nativeToUiMessageBus.Unsubscribe(m_handleSearchResultAddedMessageBinding);
			m_nativeToUiMessageBus.Unsubscribe(m_handleSearchResultRemovedMessageBinding);
		}

		void SearchResultAddRemoveHandler::HandleSearchResultAddedMessage(const SearchResultAddedMessage& message)
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

		void SearchResultAddRemoveHandler::HandleSearchResultRemovedMessage(const SearchResultRemovedMessage& message)
		{
			const Search::SearchResultModel& model(message.Model());
			m_menuOptions.RemoveItem(model.GetIdentifier());
		}
	}
}
