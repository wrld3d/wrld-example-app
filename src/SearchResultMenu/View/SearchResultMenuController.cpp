// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuController.h"
#include "IAppModeModel.h"

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
            
            void SearchResultMenuController::OnAttractModeChanged()
            {
                m_searchView.SetAttractMode(m_searchResultMenuViewModel.AttractModeEnabled());
            }
            
            void SearchResultMenuController::OnAppModelChanged()
            {
                const AppMode appMode = m_appModelModel.GetAppMode();
                if (appMode != WorldMode)
                {
                    OnSearchClosed();
                }
            }

            SearchResultMenuController::SearchResultMenuController(
                ISearchResultMenuView& searchView,
                Menu::View::IMenuView& menuView,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                ISearchResultMenuViewModel& searchResultMenuViewModel,
                IAppModeModel& appModelModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : MenuController(menuModel, menuViewModel, menuView)
                , m_searchView(searchView)
                , m_categorySearchRepository(categorySearchRepository)
                , m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_appModelModel(appModelModel)
                , m_messageBus(messageBus)
                , m_onSearchCloseTappedCallback(this, &SearchResultMenuController::OnSearchClosed)
                , m_searchQueryIssuedHandler(this, &SearchResultMenuController::OnSearchQueryPerformedMessage)
                , m_searchResultReceivedHandler(this, &SearchResultMenuController::OnSearchQueryResponseReceivedMessage)
                , m_attractModeChangedCallback(this, &SearchResultMenuController::OnAttractModeChanged)
                , m_appModeChangedCallback(this, &SearchResultMenuController::OnAppModelChanged)
            {
                m_searchView.InsertSearchClosed(m_onSearchCloseTappedCallback);
                m_messageBus.SubscribeUi(m_searchQueryIssuedHandler);
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
                m_searchResultMenuViewModel.InsertAttractModeChangedCallback(m_attractModeChangedCallback);
                m_appModelModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            }

            SearchResultMenuController::~SearchResultMenuController()
            {
                m_searchResultMenuViewModel.RemoveAttractModeChangedCallback(m_attractModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_searchQueryIssuedHandler);
                m_searchView.RemoveSearchClosed(m_onSearchCloseTappedCallback);
                m_appModelModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }
        }
    }
}
