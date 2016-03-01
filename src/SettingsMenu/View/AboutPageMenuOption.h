// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "AboutPage.h"
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class AboutPageMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                Menu::View::IMenuViewModel& m_aboutOptionContainerMenu;
                AboutPage::View::IAboutPageViewModel& m_aboutPageViewModel;

            public:
                AboutPageMenuOption(Menu::View::IMenuViewModel& aboutOptionContainerMenu,
                                    AboutPage::View::IAboutPageViewModel& aboutPageViewModel);

                ~AboutPageMenuOption();

                void Select();
            };
        }
    }
}
