// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuController.h"
#include "SearchMenuView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchMenuViewModule::SearchMenuViewModule(
                const std::string& viewName,
                WindowsNativeState& nativeState,
                Menu::View::IMenuModel& searchMenuModel,
                Menu::View::IMenuViewModel& searchMenuViewModel,
                Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                Modality::View::IModalBackgroundView& modalBackgroundView,
                ExampleAppMessaging::TMessageBus& messageBus
                )
            {
                m_pView = Eegeo_NEW(SearchMenuView)(nativeState, viewName);

                m_pController = Eegeo_NEW(SearchMenuController)(searchMenuModel,
                    searchMenuViewModel,
                    *m_pView,
                    *m_pView,
                    searchSectionViewModel,
                    categorySearchRepository,
                    modalBackgroundView,
                    messageBus);
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