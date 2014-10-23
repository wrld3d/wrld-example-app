// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageMenuOption.h"
#include "IAboutPageViewModel.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace Options
        {
            AboutPageMenuOption::AboutPageMenuOption(Menu::IMenuViewModel& aboutOptionContainerMenu,
                                                     AboutPage::IAboutPageViewModel& aboutPageViewModel)
            : m_aboutOptionContainerMenu(aboutOptionContainerMenu)
            , m_aboutPageViewModel(aboutPageViewModel)
            {
                
            }
            
            AboutPageMenuOption::~AboutPageMenuOption()
            {
                
            }
            
            void AboutPageMenuOption::Select()
            {
                m_aboutOptionContainerMenu.Close();
                m_aboutPageViewModel.Open();
            }
        }
    }
}
