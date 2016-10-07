// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuController.h"
#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ITagSearchRepository.h"
#include "IModalBackgroundView.h"

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
				builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
								{
									auto searchMenuView = context.resolve<ISearchMenuView>();
									return std::make_shared<SearchMenuController>(
											context.resolve<SearchMenuModel>(),
											context.resolve<SearchMenuViewModel>(),
											std::dynamic_pointer_cast<Menu::View::IMenuView>(searchMenuView),
											searchMenuView,
											context.resolve<SearchMenuSectionViewModel>(),
											context.resolve<TagSearch::View::ITagSearchRepository>(),
											context.resolve<Modality::View::IModalBackgroundView>(),
											context.resolve<ExampleAppMessaging::TMessageBus>());
								}).singleInstance();
			}

			void SearchMenuViewModule::RegisterUiLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<ISearchMenuView>();
				RegisterLeaf<SearchMenuController>();
			}
        }
    }
}
