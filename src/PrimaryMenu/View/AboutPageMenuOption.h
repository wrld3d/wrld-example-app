// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuOption.h"
#include "AboutPage.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace PrimaryMenu
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
