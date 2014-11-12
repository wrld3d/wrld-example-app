// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "MenuViewIncludes.h"
#include "IMenuViewController.h"
#include "ICallback.h"
#include "Menu.h"
#include "IMenuViewModel.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"

namespace ExampleApp
{
	namespace Menu
	{
		class MenuViewController : public IMenuViewController, private Eegeo::NonCopyable
		{
		protected:
			AndroidNativeState& m_nativeState;
			ExampleApp::Menu::IMenuModel& m_menuModel;
			ExampleApp::Menu::IMenuViewModel& m_menuViewModel;

			jclass m_uiViewClass;
			jobject m_uiView;

			Eegeo::Helpers::ICallback1<ExampleApp::Menu::MenuItemModel>* m_pMenuAddedCallback;
			Eegeo::Helpers::ICallback1<ExampleApp::Menu::MenuItemModel>* m_pMenuRemovedCallback;

			Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pOpenStateChangedCallback;
			Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

			bool m_dragInProgress;
			bool m_presentationDirty;

			Eegeo::Helpers::TIdentity Identity() const;

			void ExecuteTaskOnNativeThread(IMenuOptionSelectionTask* pNativeTask);

		public:
			MenuViewController(
			    const std::string& viewClassName,
			    AndroidNativeState& nativeState,
			    Menu::IMenuModel& menuModel,
			    Menu::IMenuViewModel& menuViewModel
			);

			~MenuViewController();

			virtual void UpdateUiThread(float deltaSeconds);

			virtual bool TryBeginDrag();

			virtual void HandleViewOpenCompleted();

			virtual void HandleViewCloseCompleted();

			virtual void HandleViewClicked();

			virtual void HandleDraggingViewStarted();

			virtual void HandleDraggingViewInProgress(float normalisedDragState);

			virtual void HandleDraggingViewCompleted();

			virtual void HandleItemSelected(const std::string& selection, const int index);

		protected:

			void RefreshPresentation();

			void ItemAddedCallback(ExampleApp::Menu::MenuItemModel& item);

			void ItemRemovedCallback(ExampleApp::Menu::MenuItemModel& item);

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);

			void OpenStateChangedCallback(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);
		};
	}
}
