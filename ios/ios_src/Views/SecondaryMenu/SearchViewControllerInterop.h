// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Search.h"
#include "ICallback.h"
#include "IOpenableControlViewModel.h"
#include "Menu.h"
#include "NativeToUiMessageBus.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"

@class SearchViewController;

namespace ExampleApp
{
namespace SecondaryMenu
{
class SearchViewControllerInterop : private Eegeo::NonCopyable
{
	SearchViewController* m_pInstance;
	ExampleApp::Menu::IMenuViewModel& m_menuViewModel;

	Eegeo::Helpers::TCallback1<SearchViewControllerInterop, const Search::SearchQueryPerformedMessage&> m_performedQueryCallback;
	Eegeo::Helpers::TCallback1<SearchViewControllerInterop, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseCallback;
	Eegeo::Helpers::TCallback2<SearchViewControllerInterop, OpenableControlViewModel::IOpenableControlViewModel&, float> m_menuOpenStateChangedCallback;

	ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

	void PerformedQueryCallback(const Search::SearchQueryPerformedMessage& message);

	void ReceivedQueryResponseCallback(const Search::SearchQueryResponseReceivedMessage& message);

	void HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);

public:
	SearchViewControllerInterop(SearchViewController* pInstance,
	                            ExampleApp::Menu::IMenuViewModel& menuViewModel,
	                            ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

	~SearchViewControllerInterop();
};
}
}
