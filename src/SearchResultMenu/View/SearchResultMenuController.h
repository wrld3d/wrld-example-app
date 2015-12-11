// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <vector>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ICategorySearchRepository.h"
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
                CategorySearch::View::ICategorySearchRepository& m_categorySearchRepository;
                Menu::View::IMenuOptionsModel& m_menuOptions;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                ISearchResultMenuOrder& m_order;
                
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryPerformedMessage&> m_searchQueryIssuedHandler;
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;

            private:
                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);

                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);

            protected:
                
            public:
                SearchResultMenuController(Menu::View::IMenuViewModel& searchMenuViewModel,
                                           Menu::View::IMenuOptionsModel& menuOptionsModel,
                                           ISearchResultMenuOrder& order,
                                           CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuController();
            };
        }
    }
}
