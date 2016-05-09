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
                                                               bool menuOpen):
                  m_shouldCloseMenu(menuClose)
                , m_shouldOpenMenu(menuOpen)
            {
            }


            WindowsMenuReactionModel::~WindowsMenuReactionModel()
            {
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
