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
#include "SearchMenuOptions.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionController : public Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<Menu::View::IMenuViewModel> m_searchMenuViewModel;
                const std::shared_ptr<Menu::View::IMenuOptionsModel> m_menuOptions;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                const std::shared_ptr<ISearchResultSectionOrder> m_order;
                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;
                const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel> m_searchResultPoiViewModel;
                
                Eegeo::Helpers::TCallback1<SearchResultSectionController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;
                Eegeo::Helpers::TCallback1<SearchResultSectionController, const Search::SearchQueryRemovedMessage&> m_searchQueryRemovedHandler;

            private:
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
                
                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);

            protected:
                
            public:
                SearchResultSectionController(const std::shared_ptr<SearchMenu::View::SearchMenuViewModel>& searchMenuViewModel,
                                              const std::shared_ptr<SearchResultSectionOptionsModel>& menuOptionsModel,
                                              const std::shared_ptr<ISearchResultSectionOrder>& order,
                                              const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                              const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction,
                                              const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel>& searchResultPoiViewModel);

                ~SearchResultSectionController();
            };
        }
    }
}
