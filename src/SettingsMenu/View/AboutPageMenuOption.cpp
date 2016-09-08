// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageMenuOption.h"

#include "IAboutPageViewModel.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            AboutPageMenuOption::AboutPageMenuOption(const std::shared_ptr<Menu::View::IMenuViewModel>& aboutOptionContainerMenu,
                                                     const std::shared_ptr<AboutPage::View::IAboutPageViewModel>& aboutPageViewModel)
            : m_aboutOptionContainerMenu(aboutOptionContainerMenu)
            , m_aboutPageViewModel(aboutPageViewModel)
            {

            }

            AboutPageMenuOption::~AboutPageMenuOption()
            {

            }

            void AboutPageMenuOption::Select()
            {
                m_aboutOptionContainerMenu->Close();
                m_aboutPageViewModel->Open();
            }
        }
    }
}
