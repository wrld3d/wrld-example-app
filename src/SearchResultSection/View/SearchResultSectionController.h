// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <vector>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IMenuViewModel.h"
#include "ISearchResultSectionOrder.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "SearchResultModel.h"
#include "IMenuReactionModel.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionController : public Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuViewModel& m_searchMenuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptions;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                ISearchResultSectionOrder& m_order;
                const Menu::View::IMenuReactionModel& m_menuReaction;
                SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
                
                Eegeo::Helpers::TCallback1<SearchResultSectionController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;
                Eegeo::Helpers::TCallback1<SearchResultSectionController, const Search::SearchQueryRemovedMessage&> m_searchQueryRemovedHandler;

            private:
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
                
                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);

            protected:
                
            public:
                SearchResultSectionController(Menu::View::IMenuViewModel& searchMenuViewModel,
                    Menu::View::IMenuOptionsModel& menuOptionsModel,
                    ISearchResultSectionOrder& order,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction,
                    SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);

                ~SearchResultSectionController();
            };
        }
    }
}
