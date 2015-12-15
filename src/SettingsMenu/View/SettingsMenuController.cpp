// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuController.h"

#include "AppModeChangedMessage.h"
#include "IModalBackgroundView.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuController::SettingsMenuController(Menu::View::IMenuView& menuView,
                                                           Menu::View::IMenuModel& menuModel,
                                                           Menu::View::IMenuViewModel& menuViewModel,
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : Menu::View::MenuController(menuModel, menuViewModel, menuView, messageBus)
            , m_messageBus(messageBus)
            , m_modalBackgroundView(modalBackgroundView)
            , m_appModeChangedCallback(this, &SettingsMenuController::OnAppModeChanged)
            , m_onModalBackgroundTappedCallback(this, & SettingsMenuController::OnModalBackgroundTapped)
            , m_appModeAllowsOpen(true)
            {
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }
            
            SettingsMenuController::~SettingsMenuController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
            }
            
            void SettingsMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::InteriorMode;
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                }
            }
            
            bool SettingsMenuController::TryDrag()
            {
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                    return false;
                }
                
                return MenuController::TryDrag();
            }
            
            void SettingsMenuController::OnViewClicked()
            {
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                    return;
                }
                
                MenuController::OnViewClicked();
            }
            
            void SettingsMenuController::OnModalBackgroundTapped()
            {
                if(!m_appModeAllowsOpen)
                {
                    return;
                }
                
                if(m_viewModel.IsFullyOpen())
                {
                    m_viewModel.Close();
                }
            }
        }
    }
}
