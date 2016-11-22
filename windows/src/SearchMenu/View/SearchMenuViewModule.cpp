// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewModule.h"

#include "WindowsNativeState.h"
#include "ScreenProperties.h"
#include "SearchMenuView.h"
#include "SearchMenuOptions.h"
#include "DesktopSearchMenuController.h"
#include "WindowsAppThreadAssertionMacros.h"
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
                    return std::make_shared<SearchMenuView>(context.resolve<WindowsNativeState>(),
                        "");
                }).as<ISearchMenuView>().singleInstance();

                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                {
                    auto searchMenuView = context.resolve<ISearchMenuView>();
                    return std::make_shared<DesktopSearchMenuController>(context.resolve<SearchMenuModel>(),
                        context.resolve<SearchMenuViewModel>(),
                        std::dynamic_pointer_cast<Menu::View::IMenuView>(searchMenuView),
                        searchMenuView,
                        context.resolve<SearchMenuSectionViewModel>(),
                        context.resolve<TagSearch::View::ITagSearchRepository>(),
                        context.resolve<Modality::View::IModalBackgroundView>(),
                        context.resolve<Modality::View::IModalityController>(),
                        context.resolve<ExampleAppMessaging::TMessageBus>(),
                        context.resolve<Reaction::View::IReactionModel>()
                        );
                }).singleInstance();
            }

            void SearchMenuViewModule::RegisterUiLeaves()
            {
                ASSERT_UI_THREAD
                RegisterLeaf<DesktopSearchMenuController>();
            }
        }
    }
}
