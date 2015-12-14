// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <vector>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IMenuViewModel.h"
#include "ISearchResultMenuOrder.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuController : public Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuViewModel& m_searchMenuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptions;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                ISearchResultMenuOrder& m_order;
                
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryRemovedMessage&> m_searchQueryRemovedHandler;

            private:
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
                
                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);

            protected:
                
            public:
                SearchResultMenuController(Menu::View::IMenuViewModel& searchMenuViewModel,
                                           Menu::View::IMenuOptionsModel& menuOptionsModel,
                                           ISearchResultMenuOrder& order,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuController();
            };
        }
    }
}
