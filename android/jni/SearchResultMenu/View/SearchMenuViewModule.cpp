// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		SearchMenuViewModule::SearchMenuViewModule(
		    const std::string& viewName,
		    AndroidNativeState& nativeState,
		    Menu::IMenuModel& menuModel,
		    Menu::IMenuViewModel& menuViewModel,
		    CategorySearch::ICategorySearchRepository& categorySearchRepository,
		    SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
		    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
		    ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
		)
		{
			ASSERT_UI_THREAD

			m_pMenuViewController = Eegeo_NEW(SearchMenuViewController)(
			                            viewName,
			                            nativeState,
			                            menuModel,
			                            menuViewModel,
			                            categorySearchRepository,
			                            searchResultMenuViewModel,
			                            uiToNativeMessageBus,
			                            nativeToUiMessageBus
			                        );
		}

		SearchMenuViewModule::~SearchMenuViewModule()
		{
			ASSERT_UI_THREAD

			Eegeo_DELETE m_pMenuViewController;
		}

		Menu::IMenuViewController& SearchMenuViewModule::GetMenuViewController() const
		{
			ASSERT_UI_THREAD

			return *m_pMenuViewController;
		}
	}
}
