// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSettingsMenuController.h"

#include "AppModeChangedMessage.h"
#include "IModalBackgroundView.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            DesktopSettingsMenuController::DesktopSettingsMenuController(Menu::View::IMenuView& menuView,
                                                           Menu::View::IMenuModel& menuModel,
                                                           Menu::View::IMenuViewModel& menuViewModel,
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : Menu::View::MenuController(menuModel, menuViewModel, menuView, messageBus)
            , m_messageBus(messageBus)
            , m_modalBackgroundView(modalBackgroundView)
            , m_appModeChangedCallback(this, &DesktopSettingsMenuController::OnAppModeChanged)
            , m_onModalBackgroundTappedCallback(this, & DesktopSettingsMenuController::OnModalBackgroundTapped)
            , m_appModeAllowsOpen(true)
            , m_poiClosedHandler(this, &DesktopSettingsMenuController::OnSearchResultPoiViewClosedMessage)
            , m_poiOpenedHandler(this, &DesktopSettingsMenuController::OnSearchResultPoiViewOpenedMessage)
            , m_currentAppMode(AppModes::SdkModel::AppMode::WorldMode)
            {
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                
                m_messageBus.SubscribeUi(m_appModeChangedCallback);

                m_messageBus.SubscribeNative(m_poiClosedHandler);
                m_messageBus.SubscribeNative(m_poiOpenedHandler);
            }
            
            DesktopSettingsMenuController::~DesktopSettingsMenuController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);

                m_messageBus.UnsubscribeNative(m_poiOpenedHandler);
                m_messageBus.UnsubscribeNative(m_poiClosedHandler);
                
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
            }
            
            void DesktopSettingsMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                m_currentAppMode = message.GetAppMode();
                m_appModeAllowsOpen =  m_currentAppMode != AppModes::SdkModel::InteriorMode;
                
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                }
            }
            
            bool DesktopSettingsMenuController::TryDrag()
            {
                if (!m_appModeAllowsOpen)
                {
                    m_viewModel.Close();
                    return false;
                }
                
                return MenuController::TryDrag();
            }
            
            void DesktopSettingsMenuController::OnViewClicked()
            {
                if (!m_appModeAllowsOpen)
                {
                    if (m_viewModel.IsFullyOpen())
                    {
                        m_viewModel.Close();
                    }
                    
                    return;
                }
                
                MenuController::OnViewClicked();
            }
            
            void DesktopSettingsMenuController::OnModalBackgroundTapped()
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
            
            void DesktopSettingsMenuController::OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage & message)
            {
                m_appModeAllowsOpen = false;
            }
            
            void DesktopSettingsMenuController::OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage & message)
            {
                m_appModeAllowsOpen = m_currentAppMode != AppModes::SdkModel::InteriorMode;
            }
        }
    }
}
