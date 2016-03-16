#include "WindowsMenuReactionModel.h"
// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            WindowsMenuReactionModel::WindowsMenuReactionModel(bool menuClose,
                                                               bool menuOpen,
                                                               ExampleAppMessaging::TMessageBus& messageBus):
                  m_shouldCloseMenu(menuClose)
                , m_shouldOpenMenu(menuOpen)
                , m_messageBus(messageBus)
                , m_poiOpenedHandler(this, &WindowsMenuReactionModel::OnSearchResultPoiViewOpenedMessage)
                , m_poiClosedHandler(this, &WindowsMenuReactionModel::OnSearchResultPoiViewClosedMessage)
            {
                m_messageBus.SubscribeNative(m_poiClosedHandler);
                m_messageBus.SubscribeNative(m_poiOpenedHandler);
            }


            WindowsMenuReactionModel::~WindowsMenuReactionModel()
            {
                m_messageBus.UnsubscribeNative(m_poiOpenedHandler);
                m_messageBus.UnsubscribeNative(m_poiClosedHandler);
            }

            void WindowsMenuReactionModel::OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage & message)
            {
                m_shouldCloseMenu = false;
                m_shouldOpenMenu = false;
            }

            void WindowsMenuReactionModel::OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage & message)
            {
                m_shouldCloseMenu = true;
                m_shouldOpenMenu = true;
            }

            bool WindowsMenuReactionModel::GetShouldCloseMenu() const
            {
                return m_shouldCloseMenu;
            }

            bool WindowsMenuReactionModel::GetShouldOpenMenu() const
            {
                return m_shouldOpenMenu;
            }
        }
    }
}
