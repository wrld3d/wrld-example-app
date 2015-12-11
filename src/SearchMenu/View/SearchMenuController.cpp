// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuController.h"

#include "ISearchMenuView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuController::SearchMenuController(Menu::View::IMenuModel& model,
                                                       Menu::View::IMenuViewModel& viewModel,
                                                       Menu::View::IMenuView& view,
                                                       ISearchMenuView& searchMenuView,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : Menu::View::MenuController(model, viewModel, view, messageBus)
            , m_searchMenuView(searchMenuView)
            , m_messageBus(messageBus)
            , m_appModeAllowsOpen(true)
            , m_onOpenStateChangedCallback(this, &SearchMenuController::OnOpenStateChanged)
            , m_performedQueryHandler(this, &SearchMenuController::OnSearchQueryPerformedMessage)
            , m_receivedQueryResponseHandler(this, &SearchMenuController::OnSearchQueryResponseReceivedMessage)
            , m_onSearchCallback(this, &SearchMenuController::OnSearch)
            , m_appModeChangedCallback(this, &SearchMenuController::OnAppModeChanged)
            {
                m_searchMenuView.InsertSearchPeformedCallback(m_onSearchCallback);
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenStateChangedCallback);
                
                m_messageBus.SubscribeUi(m_performedQueryHandler);
                m_messageBus.SubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }
            
            SearchMenuController::~SearchMenuController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.UnsubscribeUi(m_performedQueryHandler);
                
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_searchMenuView.RemoveSearchPeformedCallback(m_onSearchCallback);
            }
            
            void SearchMenuController::OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                if(openState != 1.f)
                {
                    m_searchMenuView.RemoveSeachKeyboard();
                }
            }
            
            void SearchMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                m_searchMenuView.DisableEditText();
            }
            
            void SearchMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                m_searchMenuView.EnableEditText();
            }
            
            void SearchMenuController::OnSearch(const std::string& searchQuery)
            {
                m_viewModel.Close();
                m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false));
            }
            
            void SearchMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::InteriorMode;
                
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                }
            }
            
            bool SearchMenuController::TryDrag()
            {
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                    return false;
                }
                
                return MenuController::TryDrag();
            }
            
            void SearchMenuController::OnViewClicked()
            {
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                    return;
                }
                MenuController::OnViewClicked();
            }
        }
    }
}