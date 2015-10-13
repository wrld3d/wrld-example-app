// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchResultMenuController.h"
#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchMenuViewModule::SearchMenuViewModule(
                const std::string& viewName,
                AndroidNativeState& nativeState,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                ISearchResultMenuViewModel& searchResultMenuViewModel,
				Menu::View::IMenuOptionsModel& menuOptionsModel,
				ISearchResultMenuOrder& searchResultMenuOrder,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                SearchMenuView* view = Eegeo_NEW(SearchMenuView)(nativeState, viewName);
                m_pView = view;

                m_pController = Eegeo_NEW(SearchResultMenu::View::SearchResultMenuController)(
                                    *view,
                                    *view,
                                    menuModel,
                                    menuViewModel,
									menuOptionsModel,
									searchResultMenuOrder,
                                    categorySearchRepository,
                                    searchResultMenuViewModel,
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
