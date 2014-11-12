// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "IMenuViewModel.h"
#include "Types.h"
#include "ICallback.h"
#include "OpenableControlViewModelIncludes.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
	namespace MenuView
	{
		template <typename TModel, typename TController>
		class MenuViewControllerInterop : private Eegeo::NonCopyable
		{
			TController* m_pInstance;
			Menu::IMenuModel& m_model;
			ExampleApp::Menu::IMenuViewModel& m_viewModel;

			Eegeo::Helpers::ICallback1<TModel>* m_pItemAddedCallback;
			Eegeo::Helpers::ICallback1<TModel>* m_pItemRemovedCallback;

			Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pOpenStateChangedCallback;
			Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

			void ItemAddedCallback(TModel& item)
			{
				[m_pInstance handleItemAdded];
			}

			void ItemRemovedCallback(TModel& item)
			{
				[m_pInstance handleItemRemoved];
			}

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
			{
				[m_pInstance handleScreenStateChanged:m_viewModel.OnScreenState()];
			}

			void OpenStateChangedCallback(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState)
			{
				[m_pInstance handleOpenStateChanged:m_viewModel.OpenState()];
			}
		public:
			MenuViewControllerInterop(TController* pInstance,
			                          Menu::IMenuModel& model,
			                          ExampleApp::Menu::IMenuViewModel& viewModel)
				: m_pInstance(pInstance)
				, m_model(model)
				, m_viewModel(viewModel)
				, m_pItemAddedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<MenuViewControllerInterop, TModel>))(this, &MenuViewControllerInterop::ItemAddedCallback))
				, m_pItemRemovedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<MenuViewControllerInterop, TModel>))(this, &MenuViewControllerInterop::ItemRemovedCallback))
				, m_pOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MenuViewControllerInterop, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &MenuViewControllerInterop::OpenStateChangedCallback))
				, m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MenuViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &MenuViewControllerInterop::OnScreenStateChangedCallback))
			{
				m_model.InsertItemAddedCallback(*m_pItemAddedCallback);
				m_model.InsertItemRemovedCallback(*m_pItemRemovedCallback);

				m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
				m_viewModel.InsertOpenStateChangedCallback(*m_pOpenStateChangedCallback);
			}

			~MenuViewControllerInterop()
			{
				m_model.RemoveItemAddedCallback(*m_pItemAddedCallback);
				m_model.RemoveItemRemovedCallback(*m_pItemRemovedCallback);

				Eegeo_DELETE m_pItemAddedCallback;
				Eegeo_DELETE m_pItemRemovedCallback;

				m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
				m_viewModel.RemoveOpenStateChangedCallback(*m_pOpenStateChangedCallback);

				Eegeo_DELETE m_pOnScreenStateChangedCallback;
				Eegeo_DELETE m_pOpenStateChangedCallback;
			}
		};
	}
}

