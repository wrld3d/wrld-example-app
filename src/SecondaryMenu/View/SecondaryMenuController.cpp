// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SecondaryMenuController.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            void SecondaryMenuController::OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                if(openState != 1.f)
                {
                    m_secondaryMenuView.RemoveSeachKeyboard();
                }
            }

            void SecondaryMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                m_secondaryMenuView.DisableEditText();
            }

            void SecondaryMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                m_secondaryMenuView.EnableEditText();
            }

            void SecondaryMenuController::OnSearch(const std::string& searchQuery)
            {
                m_viewModel.Close();
                m_messageBus.Publish(PerformedSearchMessage(searchQuery, false));
            }

            void SecondaryMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {

            }
            
            bool SecondaryMenuController::TryDrag()
            {
                return MenuController::TryDrag();
            }
            
            void SecondaryMenuController::OnViewClicked()
            {
                MenuController::OnViewClicked();
            }
            
            SecondaryMenuController::SecondaryMenuController(
                ISecondaryMenuView& secondaryMenuView,
                Menu::View::IMenuView& menuView,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : Menu::View::MenuController(menuModel, menuViewModel, menuView, messageBus)
                , m_secondaryMenuView(secondaryMenuView)
                , m_messageBus(messageBus)
                , m_onOpenStateChangedCallback(this, &SecondaryMenuController::OnOpenStateChanged)
                , m_performedQueryHandler(this, &SecondaryMenuController::OnSearchQueryPerformedMessage)
                , m_receivedQueryResponseHandler(this, &SecondaryMenuController::OnSearchQueryResponseReceivedMessage)
                , m_onSearchCallback(this, &SecondaryMenuController::OnSearch)
                , m_appModeChangedCallback(this, &SecondaryMenuController::OnAppModeChanged)
                , m_appModeAllowsOpen(true)
            {
                m_secondaryMenuView.InsertSearchPeformedCallback(m_onSearchCallback);
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_messageBus.SubscribeUi(m_performedQueryHandler);
                m_messageBus.SubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }

            SecondaryMenuController::~SecondaryMenuController()
            {
                m_messageBus.UnsubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.UnsubscribeUi(m_performedQueryHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_secondaryMenuView.RemoveSearchPeformedCallback(m_onSearchCallback);
            }
        }
    }
}
