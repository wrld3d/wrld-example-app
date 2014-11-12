// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "SecondaryMenuViewController.h"
#include "Types.h"
#include "MenuItemModel.h"
#include "IMenuViewModel.h"
#include "IMenuModel.h"
#include "ICallback.h"
#include "ISearchService.h"
#include "SearchQuery.h"
#include "ISearchQueryPerformer.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		SecondaryMenuViewController::SecondaryMenuViewController(
		    const std::string& viewClassName,
		    AndroidNativeState& nativeState,
		    ExampleApp::Menu::IMenuModel& menuModel,
		    ExampleApp::Menu::IMenuViewModel& menuViewModel,
		    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
		    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
		)
			: Menu::MenuViewController(viewClassName, nativeState, menuModel, menuViewModel)
			, m_performedQueryCallback(this, &SecondaryMenuViewController::PerformedQueryCallback)
			, m_receivedQueryResponseCallback(this, &SecondaryMenuViewController::ReceivedQueryResponseCallback)
			, m_menuOpenStateChangedCallback(this, &SecondaryMenuViewController::HandleOpenStateChanged)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
		{
			ASSERT_UI_THREAD

			m_menuViewModel.InsertOpenStateChangedCallback(m_menuOpenStateChangedCallback);
			m_nativeToUiMessageBus.Subscribe(m_performedQueryCallback);
			m_nativeToUiMessageBus.Subscribe(m_receivedQueryResponseCallback);
		}

		SecondaryMenuViewController::~SecondaryMenuViewController()
		{
			ASSERT_UI_THREAD

			m_nativeToUiMessageBus.Unsubscribe(m_performedQueryCallback);
			m_nativeToUiMessageBus.Unsubscribe(m_receivedQueryResponseCallback);
			m_menuViewModel.RemoveOpenStateChangedCallback(m_menuOpenStateChangedCallback);
		}

		void SecondaryMenuViewController::HandleSearch(const std::string& searchQuery)
		{
			ASSERT_UI_THREAD

			m_menuViewModel.Close();

			m_uiToNativeMessageBus.Publish(PerformedSearchMessage(searchQuery, false));
		}

		void SecondaryMenuViewController::HandleOpenStateChanged(
		    OpenableControlViewModel::IOpenableControlViewModel& viewModel,
		    float& openState)
		{
			ASSERT_UI_THREAD

			if(openState != 1.f)
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;
				jmethodID removeSeachKeyboard = env->GetMethodID(m_uiViewClass, "removeSeachKeyboard", "()V");
				env->CallVoidMethod(m_uiView, removeSeachKeyboard);
			}
		}

		void SecondaryMenuViewController::PerformedQueryCallback(const Search::SearchQueryPerformedMessage& message)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID disableEditText = env->GetMethodID(m_uiViewClass, "disableEditText", "()V");
			env->CallVoidMethod(m_uiView, disableEditText);
		}

		void SecondaryMenuViewController::ReceivedQueryResponseCallback(const Search::SearchQueryResponseReceivedMessage& message)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID enableEditText = env->GetMethodID(m_uiViewClass, "enableEditText", "()V");
			env->CallVoidMethod(m_uiView, enableEditText);
		}
	}
}
