// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuView.h"
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "IMenuSectionViewModel.h"
#include "IUpdateableViewController.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuController : private Eegeo::NonCopyable, public ViewControllerUpdater::View::IUpdateableViewController
            {
            private:
                Eegeo::Helpers::TCallback0<MenuController> m_onClickedCallback;
                Eegeo::Helpers::TCallback0<MenuController> m_onViewOpenedCallback;
                Eegeo::Helpers::TCallback0<MenuController> m_onViewOpenStartedCallback;
                Eegeo::Helpers::TCallback0<MenuController> m_onViewClosedCallback;
                Eegeo::Helpers::TCallback0<MenuController> m_onDragStartedCallback;
                Eegeo::Helpers::TCallback1<MenuController, float> m_onDragCallback;
                Eegeo::Helpers::TCallback0<MenuController> m_onDragCompletedCallback;
                Eegeo::Helpers::TCallback2<MenuController, int, int> m_onItemSelectedCallback;
                Eegeo::Helpers::TCallback1<MenuController, MenuItemModel> m_onItemAddedCallback;
                Eegeo::Helpers::TCallback1<MenuController, MenuItemModel> m_onItemRemovedCallback;
                Eegeo::Helpers::TCallback2<MenuController, ScreenControl::View::IScreenControlViewModel&, float> m_onScreenStateChanged;
                Eegeo::Helpers::TCallback2<MenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenableStateChanged;
                Eegeo::Helpers::TCallback2<MenuController, IMenuSectionViewModel&, bool> m_onMenuSectionExpandedStateChanged;
                Eegeo::Helpers::TCallback1<MenuController, const AppModes::AppModeChangedMessage&> m_onAppModeChanged;
                Eegeo::Helpers::TCallback1<MenuController, const InteriorsExplorer::InteriorsExplorerStateChangedMessage& > m_onInteriorStateChangedCallback;

                Eegeo::Helpers::TFunc0<MenuController, bool> m_tryDragFunc;

                ExampleAppMessaging::TMessageBus& m_messageBus;

            protected:
                IMenuModel& m_model;
                IMenuViewModel& m_viewModel;
                IMenuView& m_view;
                bool m_dragInProgress;
                bool m_presentationDirty;
                bool m_menuContentsChanged;
                bool m_forceClose;

                virtual void OnMenuSectionExpandeStateChanged(IMenuSectionViewModel& menuSectionViewModel, bool& expanded);
                
                virtual void OnOpenableStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& state);

                virtual void OnScreenControlStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

                virtual bool TryDrag();

                virtual void RefreshPresentation(bool forceRefresh);

                virtual void UpdateUiThread(float dt);

                virtual void OnViewClicked();

                virtual void OnViewOpened();

                virtual void OnViewOpenStarted();

                virtual void OnViewClosed();

                Eegeo::Helpers::TIdentity Identity() const;

                virtual void OnDragStarted();

                virtual void OnDrag(float& value);

                virtual void OnDragCompleted();

                virtual void OnItemAdded(MenuItemModel& item);

                virtual void OnItemRemoved(MenuItemModel& item);

                virtual void OnItemSelected(int& sectionIndex, int& itemIndex);

                virtual void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

                virtual void OnInteriorStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message);

            public:
                MenuController(
                    IMenuModel& model,
                    IMenuViewModel& viewModel,
                    IMenuView& view,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~MenuController();
            };
        }
    }
}
