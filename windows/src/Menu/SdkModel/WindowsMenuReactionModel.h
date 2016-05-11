// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IMenuReactionModel.h"
#include "BidirectionalBus.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoiViewClosedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class WindowsMenuReactionModel : public Menu::View::IMenuReactionModel
            {
                bool m_shouldCloseMenu;
                bool m_shouldOpenMenu;

            public:
                WindowsMenuReactionModel(bool menuClose,
                                         bool menuOpen);

                ~WindowsMenuReactionModel();

                bool GetShouldCloseMenu() const;

                bool GetShouldOpenMenu() const;
            };
        }
    }
}
