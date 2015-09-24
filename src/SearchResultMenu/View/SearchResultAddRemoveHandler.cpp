// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultAddRemoveHandler.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultAddRemoveHandler::SearchResultAddRemoveHandler(
                Menu::View::IMenuOptionsModel& menuOptions,
                Menu::View::IMenuViewModel& menuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_menuOptions(menuOptions)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_handleSearchResultAddedMessageBinding(this, &SearchResultAddRemoveHandler::OnSearchResultAddedMessage)
                , m_handleSearchResultRemovedMessageBinding(this, &SearchResultAddRemoveHandler::OnSearchResultRemovedMessage)
            {
                m_messageBus.SubscribeUi(m_handleSearchResultAddedMessageBinding);
                m_messageBus.SubscribeUi(m_handleSearchResultRemovedMessageBinding);
            }

            SearchResultAddRemoveHandler::~SearchResultAddRemoveHandler()
            {
                m_messageBus.UnsubscribeUi(m_handleSearchResultAddedMessageBinding);
                m_messageBus.UnsubscribeUi(m_handleSearchResultRemovedMessageBinding);
            }

            void SearchResultAddRemoveHandler::OnSearchResultAddedMessage(const SearchResultAddedMessage& message)
            {
                const Search::SdkModel::SearchResultModel& model(message.Model());

                m_menuOptions.AddItem(
                    model.GetIdentifier(),
                    model.GetTitle(),
                    model.GetSubtitle(),
                    model.GetCategory(),
                    Eegeo_NEW(SearchResultItemModel)(
                        model.GetTitle(),
                        model.GetLocation().ToECEF(),
                        m_menuViewModel,
                        m_messageBus)
                );
            }

            void SearchResultAddRemoveHandler::OnSearchResultRemovedMessage(const SearchResultRemovedMessage& message)
            {
                const Search::SdkModel::SearchResultModel& model(message.Model());
                m_menuOptions.RemoveItem(model.GetIdentifier());
            }
        }
    }
}
