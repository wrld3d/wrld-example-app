// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "SearchMenuViewController.h"
#include "Types.h"
#include "MenuItemModel.h"
#include "IMenuViewModel.h"
#include "IMenuModel.h"
#include "ICallback.h"
#include "ISearchQueryPerformer.h"
#include "ISearchService.h"
#include "ICategorySearchRepository.h"
#include "SearchResultModel.h"
#include "ISearchResultMenuViewModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchResultViewClearedMessage.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		SearchMenuViewController::SearchMenuViewController(
		    const std::string& viewClassName,
		    AndroidNativeState& nativeState,
		    ExampleApp::Menu::IMenuModel& menuModel,
		    ExampleApp::Menu::IMenuViewModel& menuViewModel,
		    CategorySearch::ICategorySearchRepository& categorySearchRepository,
		    SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
		    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
		    ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
		)
			: Menu::MenuViewController(viewClassName, nativeState, menuModel, menuViewModel)
			, m_searchQueryIssuedCallback(this, &SearchMenuViewController::HandleSearchQueryIssued)
			, m_searchResultReceivedCallback(this, &SearchMenuViewController::HandleSearchResultReceived)
			, m_categorySearchRepository(categorySearchRepository)
			, m_searchResultMenuViewModel(searchResultMenuViewModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
		{
			ASSERT_UI_THREAD
			m_nativeToUiMessageBus.Subscribe(m_searchResultReceivedCallback);
			m_nativeToUiMessageBus.Subscribe(m_searchQueryIssuedCallback);
		}

		SearchMenuViewController::~SearchMenuViewController()
		{
			ASSERT_UI_THREAD
			m_nativeToUiMessageBus.Unsubscribe(m_searchResultReceivedCallback);
			m_nativeToUiMessageBus.Unsubscribe(m_searchQueryIssuedCallback);
		}

		bool SearchMenuViewController::TryBeginDrag()
		{
			ASSERT_UI_THREAD

			if(m_searchResultMenuViewModel.CanInteract())
			{
				return MenuViewController::TryBeginDrag();
			}

			return false;
		}

		void SearchMenuViewController::HandleViewClicked()
		{
			ASSERT_UI_THREAD

			if(m_searchResultMenuViewModel.CanInteract())
			{
				MenuViewController::HandleViewClicked();
			}
		}

		void SearchMenuViewController::HandleClosed()
		{
			ASSERT_UI_THREAD

			m_uiToNativeMessageBus.Publish(ExampleApp::SearchResultMenu::SearchResultViewClearedMessage());
			m_menuViewModel.RemoveFromScreen();
		}

		void SearchMenuViewController::RefreshViewHeader(const Search::SearchQuery& query, bool queryPending, int numResult)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID updateHeaderMethod = env->GetMethodID(m_uiViewClass, "updateHeader", "(Ljava/lang/String;ZI)V");
			std::string headerString = CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, query);
			jstring queryString = env->NewStringUTF(headerString.c_str());

			env->CallVoidMethod(m_uiView, updateHeaderMethod, queryString, queryPending, numResult);
			env->DeleteLocalRef(queryString);
		}

		void SearchMenuViewController::HandleSearchQueryIssued(const Search::SearchQueryPerformedMessage& message)
		{
			ASSERT_UI_THREAD

			RefreshViewHeader(message.Query(), true, 0);
		}

		void SearchMenuViewController::HandleSearchResultReceived(const Search::SearchQueryResponseReceivedMessage& message)
		{
			ASSERT_UI_THREAD

			RefreshViewHeader(message.GetQuery(), false, message.GetResults().size());
		}
	}
}
