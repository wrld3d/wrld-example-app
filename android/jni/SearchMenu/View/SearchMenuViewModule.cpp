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
				ASSERT_UI_THREAD

				builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
						{
							const std::string viewName = "com/eegeo/searchmenu/SearchMenuView";
							return std::make_shared<SearchMenuView>(context.resolve<AndroidNativeState>(), viewName);
						}).as<ISearchMenuView>().singleInstance();
			}
        }
    }
}
