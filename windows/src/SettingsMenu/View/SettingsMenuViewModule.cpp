// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsNativeState.h"
#include "Menu.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuController.h"
#include "SettingsMenuView.h"
#include "IModalBackgroundView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "DesktopSettingsMenuController.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            void SettingsMenuViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                {
                    const std::string viewName = "";
                    return std::make_shared<SettingsMenuView>(context.resolve<WindowsNativeState>(), viewName);
                }).as<ISettingsMenuView>().singleInstance();

                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                {
                    auto settingsMenuView = context.resolve<ISettingsMenuView>();

                    return std::make_shared<DesktopSettingsMenuController>(std::dynamic_pointer_cast<Menu::View::IMenuView>(settingsMenuView),
                        context.resolve<SettingsMenuModel>(),
                        context.resolve<SettingsMenuViewModel>(),
                        context.resolve<Modality::View::IModalBackgroundView>(),
                        std::dynamic_pointer_cast<Menu::View::IMenuView>(settingsMenuView),
                        context.resolve<ExampleAppMessaging::TMessageBus>());
                }).singleInstance();
            }

            void SettingsMenuViewModule::RegisterUiLeaves()
            {
                RegisterLeaf<DesktopSettingsMenuController>();
            }
        }
    }
}
