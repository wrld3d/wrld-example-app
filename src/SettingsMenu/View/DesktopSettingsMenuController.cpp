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
                                                           Menu::View::IMenuView& searchMenuView,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : Menu::View::MenuController(menuModel, menuViewModel, menuView, messageBus)
            , m_messageBus(messageBus)
            , m_modalBackgroundView(modalBackgroundView)
            , m_onModalBackgroundTappedCallback(this, & DesktopSettingsMenuController::OnModalBackgroundTapped)
            , m_appModeAllowsOpen(true)
            , m_poiClosedHandler(this, &DesktopSettingsMenuController::OnSearchResultPoiViewClosedMessage)
            , m_poiOpenedHandler(this, &DesktopSettingsMenuController::OnSearchResultPoiViewOpenedMessage)
            , m_onViewOpenedCallback(this, &DesktopSettingsMenuController::OnSearchMenuOpened)
            , m_onViewClosedCallback(this, &DesktopSettingsMenuController::OnSearchMenuClosed)
            , m_searchMenuView(searchMenuView)
            {
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                
                m_messageBus.SubscribeNative(m_poiClosedHandler);
                m_messageBus.SubscribeNative(m_poiOpenedHandler);

                m_searchMenuView.InsertOnViewOpened(m_onViewOpenedCallback);
                m_searchMenuView.InsertOnViewClosed(m_onViewClosedCallback);

                m_isControlOpen[Control::SearchMenu] = false;
                m_isControlOpen[Control::POICard] = false;
            }
            
            DesktopSettingsMenuController::~DesktopSettingsMenuController()
            {
                m_messageBus.UnsubscribeNative(m_poiOpenedHandler);
                m_messageBus.UnsubscribeNative(m_poiClosedHandler);
                
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);

                m_searchMenuView.RemoveOnViewOpened(m_onViewOpenedCallback);
                m_searchMenuView.RemoveOnViewClosed(m_onViewClosedCallback);
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
                
                if(m_viewModel.IsFullyOpen() && !m_view.IsAnimating())
                {
                    m_viewModel.Close();
                }
            }
            
            void DesktopSettingsMenuController::OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage & message)
            {
                m_viewModel.RemoveFromScreen();
                
                m_isControlOpen[Control::POICard] = true;
            }
            
            void DesktopSettingsMenuController::OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage & message)
            {
                if (!m_isControlOpen[Control::SearchMenu])
                {
                    m_viewModel.AddToScreen();
                }
                
                m_isControlOpen[Control::POICard] = false;

            }

            void DesktopSettingsMenuController::OnSearchMenuOpened()
            {
                m_viewModel.RemoveFromScreen();
                m_isControlOpen[Control::SearchMenu] = true;
            }
            
            void DesktopSettingsMenuController::OnSearchMenuClosed()
            {
                if (!m_isControlOpen[Control::POICard])
                {
                    m_viewModel.AddToScreen();
                }

                m_isControlOpen[Control::SearchMenu] = false;
            }
        }
    }
}
