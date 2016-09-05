// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuModel : public Menu::View::MenuModel
            {
            };
            
            class OptionsMenuModel : public Menu::View::MenuModel
            {
            };
            
            class AboutMenuModel : public Menu::View::MenuModel
            {
            };
            
            class SettingsMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                SettingsMenuOptionsModel(const std::shared_ptr<SettingsMenuModel>& settingsMenuModel) : Menu::View::MenuOptionsModel(*settingsMenuModel)
                {
                }
            };
            
            class OptionsMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                OptionsMenuOptionsModel(const std::shared_ptr<OptionsMenuModel>& optionsMenuModel) : Menu::View::MenuOptionsModel(*optionsMenuModel)
                {
                }
            };
            
            class AboutMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                AboutMenuOptionsModel(const std::shared_ptr<AboutMenuModel>& aboutMenuModel) : Menu::View::MenuOptionsModel(*aboutMenuModel)
                {
                }
            };
            
            class SettingsMenuViewModel : public Menu::View::MenuViewModel
            {
            public:
                SettingsMenuViewModel(bool isInitiallyOnScreen,
                                      const std::shared_ptr<Eegeo::Helpers::IIdentityProvider>& identity,
                                      const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : Menu::View::MenuViewModel(isInitiallyOnScreen, identity->GetNextIdentity(), reactionControllerModel)
                {
                }
            };
        }
    }
}
