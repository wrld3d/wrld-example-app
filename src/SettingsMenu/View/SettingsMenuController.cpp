// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuController.h"

#include "AppModeChangedMessage.h"
#include "IModalBackgroundView.h"
#include "IAppModeModel.h"

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
            , m_modalBackgroundView(modalBackgroundView)
            , m_onModalBackgroundTappedCallback(this, & SettingsMenuController::OnModalBackgroundTapped)
            {
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
            }
            
            SettingsMenuController::~SettingsMenuController()
            {
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
            }
            
            bool SettingsMenuController::TryDrag()
            {
                return MenuController::TryDrag();
            }
            
            void SettingsMenuController::OnViewClicked()
            {
                MenuController::OnViewClicked();
            }
            
            void SettingsMenuController::OnModalBackgroundTapped()
            {
                if(m_viewModel.IsFullyOpen() && !m_view.IsAnimating())
                {
                    m_viewModel.Close();
                }
            }
        }
    }
}
