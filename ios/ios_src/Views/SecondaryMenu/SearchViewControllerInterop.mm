// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchViewControllerInterop.h"
#include "SearchViewController.h"
#include "ISearchService.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		SearchViewControllerInterop::SearchViewControllerInterop(SearchViewController* pInstance,
		        ExampleApp::Menu::IMenuViewModel& menuViewModel,
		        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_pInstance(pInstance)
			, m_menuViewModel(menuViewModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_performedQueryCallback(this, &SearchViewControllerInterop::PerformedQueryCallback)
			, m_receivedQueryResponseCallback(this, &SearchViewControllerInterop::ReceivedQueryResponseCallback)
			, m_menuOpenStateChangedCallback(this, &SearchViewControllerInterop::HandleOpenStateChanged)
		{
			m_menuViewModel.InsertOpenStateChangedCallback(m_menuOpenStateChangedCallback);
			m_nativeToUiMessageBus.Subscribe(m_performedQueryCallback);
			m_nativeToUiMessageBus.Subscribe(m_receivedQueryResponseCallback);
		}

		SearchViewControllerInterop::~SearchViewControllerInterop()
		{
			m_nativeToUiMessageBus.Unsubscribe(m_performedQueryCallback);
			m_nativeToUiMessageBus.Unsubscribe(m_receivedQueryResponseCallback);
			m_menuViewModel.RemoveOpenStateChangedCallback(m_menuOpenStateChangedCallback);
		}

		void SearchViewControllerInterop::PerformedQueryCallback(const Search::SearchQueryPerformedMessage& message)
		{
			[m_pInstance disableEdit];
		}

		void SearchViewControllerInterop::ReceivedQueryResponseCallback(const Search::SearchQueryResponseReceivedMessage& message)
		{
			[m_pInstance enableEdit];
		}

		void SearchViewControllerInterop::HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel,
		        float& openState)
		{
			if(openState != 1.f)
			{
				[m_pInstance removeSeachKeyboard];
			}
		}
	}
}
