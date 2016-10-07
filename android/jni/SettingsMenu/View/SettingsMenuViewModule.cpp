// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuController.h"
#include "SettingsMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IMenuView.h"
#include "IModalBackgroundView.h"

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
							const std::string viewName = "com/eegeo/settingsmenu/SettingsMenuView";
							return std::make_shared<SettingsMenuView>(context.resolve<AndroidNativeState>(), viewName);
						}).as<ISettingsMenuView>().singleInstance();
				builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
								{
									auto settingsMenuView = context.resolve<ISettingsMenuView>();
									return std::make_shared<SettingsMenuController>(std::dynamic_pointer_cast<Menu::View::IMenuView>(settingsMenuView),
											context.resolve<SettingsMenuModel>(),
											context.resolve<SettingsMenuViewModel>(),
											context.resolve<Modality::View::IModalBackgroundView>(),
											context.resolve<ExampleAppMessaging::TMessageBus>());
								}).singleInstance();
			}

			void SettingsMenuViewModule::RegisterUiLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<ISettingsMenuView>();
				RegisterLeaf<SettingsMenuController>();
			}
        }
    }
}
