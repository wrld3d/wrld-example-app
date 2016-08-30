// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "MyPinCreation.h"
#include "MyPinCreationStage.h"
#include "IMyPinCreationCompositeViewModel.h"
#include "Menu.h"
#include "ScreenControlViewModelBase.h"
#include "Search.h"
#include "BidirectionalBus.h"
#include "MyPinCreationStateChangedMessage.h"
#include <memory>
namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationCompositeViewModel : public IMyPinCreationCompositeViewModel
            {
            public:

                MyPinCreationCompositeViewModel(const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                const std::shared_ptr<IMyPinCreationInitiationViewModel>& initiationViewModel,
                                                const std::shared_ptr<IMyPinCreationConfirmationViewModel>& confirmationViewModel,
                                                const std::shared_ptr<ExampleApp::Menu::View::IMenuViewModel>& searchMenuViewModel,
                                                const std::shared_ptr<ExampleApp::Menu::View::IMenuViewModel>& settingsMenuViewModel,
                                                const std::shared_ptr<ScreenControl::View::IScreenControlViewModel>& interiorControlViewModel);

                ~MyPinCreationCompositeViewModel();

                void HandlePoiRingStateChanged(MyPinCreationStage& stage);
                void OnPoiRingStateChangedMessage(const MyPinCreationStateChangedMessage& message);
                void HandleSettingsMenuStateChanged(ScreenControl::View::IScreenControlViewModel &viewModel, float& onScreenState);

            private:
                Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, const MyPinCreationStateChangedMessage&> m_stateChangeHandler;
                Eegeo::Helpers::TCallback2<MyPinCreationCompositeViewModel, ScreenControl::View::IScreenControlViewModel&, float> m_settingsMenuStateChangedCallback;

                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<IMyPinCreationInitiationViewModel> m_initiationViewModel;
                const std::shared_ptr<IMyPinCreationConfirmationViewModel> m_confirmationViewModel;
                const std::shared_ptr<ScreenControl::View::IScreenControlViewModel> m_interiorControlViewModel;
                const std::shared_ptr<ExampleApp::Menu::View::IMenuViewModel> m_searchMenuViewModel;
                const std::shared_ptr<ExampleApp::Menu::View::IMenuViewModel> m_settingsMenuViewModel;
            };
        }
    }
}
