// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuController.h"
#include "SettingsMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

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
			}

			void SettingsMenuViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("SettingsMenuViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<ISettingsMenuView>();
				Eegeo_TTY("SettingsMenuViewModule::RegisterUiLeaves end");
			}
        }
    }
}
