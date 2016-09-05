// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "Menu.h"
#include "Options.h"
#include "Types.h"

#include <memory>

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class OptionsMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                const std::shared_ptr<Menu::View::IMenuViewModel> m_containerMenu;
                const std::shared_ptr<Options::View::IOptionsViewModel> m_optionsViewModel;
                
            public:
                OptionsMenuOption(const std::shared_ptr<Menu::View::IMenuViewModel>& containerMenu,
                                  const std::shared_ptr<Options::View::IOptionsViewModel>& optionsViewModel);
                
                ~OptionsMenuOption();
                
                void Select();
            };
        }
    }
}
