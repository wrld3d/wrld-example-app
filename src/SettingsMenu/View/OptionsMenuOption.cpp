// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsMenuOption.h"

#include "IMenuViewModel.h"
#include "IOptionsViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            OptionsMenuOption::OptionsMenuOption(Menu::View::IMenuViewModel& containerMenu,
                                                 Options::View::IOptionsViewModel& optionsViewModel)
            : m_containerMenu(containerMenu)
            , m_optionsViewModel(optionsViewModel)
            {
                
            }
            
            OptionsMenuOption::~OptionsMenuOption()
            {
                
            }
            
            void OptionsMenuOption::Select()
            {
                m_containerMenu.Close();
                m_optionsViewModel.Open();
            }
        }
    }
}
