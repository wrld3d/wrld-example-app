// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "IMenuOptionsModel.h"
#include "SearchResultModel.h"
#include "SearchResultItemModel.h"
#include "IMenuViewModel.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultAddRemoveHandler : private Eegeo::NonCopyable
            {
                Menu::View::IMenuOptionsModel& m_menuOptions;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<SearchResultAddRemoveHandler, const SearchResultAddedMessage&> m_handleSearchResultAddedMessageBinding;
                Eegeo::Helpers::TCallback1<SearchResultAddRemoveHandler, const SearchResultRemovedMessage&> m_handleSearchResultRemovedMessageBinding;

                void OnSearchResultAddedMessage(const SearchResultAddedMessage& message);

                void OnSearchResultRemovedMessage(const SearchResultRemovedMessage& message);
                
                Menu::View::IMenuOption* GetMenuOptionByVendor(const std::string& vendor, const Search::SdkModel::SearchResultModel model);

            public:
                SearchResultAddRemoveHandler(Menu::View::IMenuOptionsModel& menuOptions,
                                             Menu::View::IMenuViewModel& menuViewModel,
                                             ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultAddRemoveHandler();
            };
        }
    }
}
