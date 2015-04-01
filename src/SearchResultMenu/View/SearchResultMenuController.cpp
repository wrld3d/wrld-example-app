// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuController.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            void SearchResultMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                std::string headerString = CategorySearch::View::GetPresentationStringForQuery(m_categorySearchRepository, message.Query());
                m_searchView.SetHeader(headerString, true, 0);
                m_searchResultMenuViewModel.SetHasSearchQueryInFlight(true);
            }

            void SearchResultMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                std::string headerString = CategorySearch::View::GetPresentationStringForQuery(m_categorySearchRepository, message.GetQuery());
                m_searchView.SetHeader(headerString, false, message.GetResults().size());
                m_searchResultMenuViewModel.SetHasSearchQueryInFlight(false);
            }

            void SearchResultMenuController::OnViewClicked()
            {
                if(m_searchResultMenuViewModel.CanInteract())
                {
                    MenuController::OnViewClicked();
                }
            }

            bool SearchResultMenuController::TryDrag()
            {
                if(m_searchResultMenuViewModel.CanInteract())
                {
                    return MenuController::TryDrag();
                }

                return false;
            }

            void SearchResultMenuController::OnSearchClosed()
            {
                m_messageBus.Publish(ExampleApp::SearchResultMenu::SearchResultViewClearedMessage());
                m_viewModel.RemoveFromScreen();
            }

            SearchResultMenuController::SearchResultMenuController(
                ISearchResultMenuView& searchView,
                Menu::View::IMenuView& menuView,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                ISearchResultMenuViewModel& searchResultMenuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : MenuController(menuModel, menuViewModel, menuView)
                , m_searchView(searchView)
                , m_categorySearchRepository(categorySearchRepository)
                , m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_messageBus(messageBus)
                , m_onSearchCloseTappedCallback(this, &SearchResultMenuController::OnSearchClosed)
                , m_searchQueryIssuedHandler(this, &SearchResultMenuController::OnSearchQueryPerformedMessage)
                , m_searchResultReceivedHandler(this, &SearchResultMenuController::OnSearchQueryResponseReceivedMessage)
            {
                m_searchView.InsertSearchClosed(m_onSearchCloseTappedCallback);
                m_messageBus.SubscribeUi(m_searchQueryIssuedHandler);
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
            }

            SearchResultMenuController::~SearchResultMenuController()
            {
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_searchQueryIssuedHandler);
                m_searchView.RemoveSearchClosed(m_onSearchCloseTappedCallback);
            }
        }
    }
}
