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
            SearchMenuViewModule::SearchMenuViewModule(
                const std::string& viewName,
                AndroidNativeState& nativeState,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                TagSearch::View::ITagSearchRepository& tagSearchRepository,
				Menu::View::IMenuOptionsModel& menuOptionsModel,
                Modality::View::IModalBackgroundView& modalBackgroundView,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                SearchMenuView* view = Eegeo_NEW(SearchMenuView)(nativeState, viewName);
                m_pView = view;

                m_pController = Eegeo_NEW(SearchMenu::View::SearchMenuController)(
                                    menuModel,
                                    menuViewModel,
									*view,
									*view,
									searchSectionViewModel,
                                    tagSearchRepository,
									modalBackgroundView,
                                    messageBus
                                );
            }

            SearchMenuViewModule::~SearchMenuViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            Menu::View::MenuController& SearchMenuViewModule::GetMenuController() const
            {
                ASSERT_UI_THREAD
                return *m_pController;
            }

            Menu::View::IMenuView& SearchMenuViewModule::GetMenuView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
