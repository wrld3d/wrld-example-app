// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <vector>
#include "BidirectionalBus.h"
#include "ISearchResultMenuOrder.h"
#include "ISearchResultMenuView.h"
#include "SearchResultModel.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "ICallback.h"
#include "ISearchResultMenuViewModel.h"
#include "ICategorySearchRepository.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuController : public Menu::View::MenuController
            {
            private:
                ISearchResultMenuView& m_searchView;
                CategorySearch::View::ICategorySearchRepository& m_categorySearchRepository;
                View::ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptions;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                ISearchResultMenuOrder& m_order;
                
                bool m_appModeAllowsOpen;
                

                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryPerformedMessage&> m_searchQueryIssuedHandler;
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;
                Eegeo::Helpers::TCallback0<SearchResultMenuController> m_onSearchCloseTappedCallback;
                
                Eegeo::Helpers::TCallback0<SearchResultMenuController> m_attractModeChangedCallback;
                
                Eegeo::Helpers::TCallback1<SearchResultMenuController, const AppModes::AppModeChangedMessage&>  m_appModeChangedHandler;

            private:
                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);

                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);

            protected:
                void OnViewClicked();

                bool TryDrag();

                void OnSearchClosed();
                
                void OnAttractModeChanged();
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
            public:
                SearchResultMenuController(
                    ISearchResultMenuView& searchView,
                    Menu::View::IMenuView& menuView,
                    Menu::View::IMenuModel& menuModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    Menu::View::IMenuOptionsModel& menuOptionsModel,
                    ISearchResultMenuOrder& order,
                    CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                    View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SearchResultMenuController();
            };
        }
    }
}
