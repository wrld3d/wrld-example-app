// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "AboutPage.h"
#include "Menu.h"
#include "Types.h"
#include <memory>

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class AboutPageMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                const std::shared_ptr<Menu::View::IMenuViewModel> m_aboutOptionContainerMenu;
                const std::shared_ptr<AboutPage::View::IAboutPageViewModel> m_aboutPageViewModel;

            public:
                AboutPageMenuOption(const std::shared_ptr<Menu::View::IMenuViewModel>& aboutOptionContainerMenu,
                                    const std::shared_ptr<AboutPage::View::IAboutPageViewModel>& aboutPageViewModel);

                ~AboutPageMenuOption();

                void Select();
            };
        }
    }
}
