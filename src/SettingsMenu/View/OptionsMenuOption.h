// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "Menu.h"
#include "Options.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class OptionsMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                Menu::View::IMenuViewModel& m_containerMenu;
                Options::View::IOptionsViewModel& m_optionsViewModel;
                
            public:
                OptionsMenuOption(Menu::View::IMenuViewModel& containerMenu,
                                  Options::View::IOptionsViewModel& optionsViewModel);
                
                ~OptionsMenuOption();
                
                void Select();
            };
        }
    }
}
