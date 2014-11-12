// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "AndroidNativeState.h"
#include "Types.h"
#include "MenuViewIncludes.h"
#include "MenuViewController.h"
#include "ICallback.h"
#include "Menu.h"
#include "IMenuViewModel.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"
#include "Search.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		class SecondaryMenuViewController : public Menu::MenuViewController
		{
			Eegeo::Helpers::TCallback1<SecondaryMenuViewController, const Search::SearchQueryPerformedMessage&> m_performedQueryCallback;
			Eegeo::Helpers::TCallback1<SecondaryMenuViewController, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseCallback;
			Eegeo::Helpers::TCallback2<SecondaryMenuViewController, OpenableControlViewModel::IOpenableControlViewModel&, float> m_menuOpenStateChangedCallback;

			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

		public:
			SecondaryMenuViewController(
			    const std::string& viewClassName,
			    AndroidNativeState& nativeState,
			    Menu::IMenuModel& menuModel,
			    Menu::IMenuViewModel& menuViewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
			);

			~SecondaryMenuViewController();

			void HandleSearch(const std::string& query);

		private:

			void PerformedQueryCallback(const Search::SearchQueryPerformedMessage& message);

			void ReceivedQueryResponseCallback(const Search::SearchQueryResponseReceivedMessage& message);

			void HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);

		};
	}
}
