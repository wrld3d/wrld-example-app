// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuController.h"
#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
			void SearchMenuViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
						{
							const std::string viewName = "com/eegeo/searchmenu/SearchMenuView";
							return std::make_shared<SearchMenuView>(context.resolve<AndroidNativeState>(), viewName);
						}).as<ISearchMenuView>().singleInstance();
			}

			void SearchMenuViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("SearchMenuViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<ISearchMenuView>();
				Eegeo_TTY("SearchMenuViewModule::RegisterUiLeaves end");
			}
        }
    }
}
