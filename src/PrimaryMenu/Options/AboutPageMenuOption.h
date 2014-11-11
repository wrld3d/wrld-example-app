// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuOption.h"
#include "AboutPage.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace Options
        {
            class AboutPageMenuOption : public Menu::IMenuOption, private Eegeo::NonCopyable
            {
                Menu::IMenuViewModel& m_aboutOptionContainerMenu;
                AboutPage::IAboutPageViewModel& m_aboutPageViewModel;
                
            public:
                AboutPageMenuOption(Menu::IMenuViewModel& aboutOptionContainerMenu,
                                    AboutPage::IAboutPageViewModel& aboutPageViewModel);
                
                ~AboutPageMenuOption();

                void Select();
            };
        }
    }
}
