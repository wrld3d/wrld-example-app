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
#include "Watermark.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationCompositeViewModel : public IMyPinCreationCompositeViewModel
            {
            public:

                MyPinCreationCompositeViewModel(ExampleAppMessaging::TMessageBus& messageBus,
                                                IMyPinCreationInitiationViewModel& initiationViewModel,
                                                IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                                ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                                                ExampleApp::Watermark::View::IWatermarkViewModel& watermarkViewModel);

                ~MyPinCreationCompositeViewModel();

                void HandlePoiRingStateChanged(MyPinCreationStage& stage);
                void OnPoiRingStateChangedMessage(const MyPinCreationStateChangedMessage& message);
                void HandleSettingsMenuStateChanged(ScreenControl::View::IScreenControlViewModel &viewModel, float& onScreenState);

            private:
                Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, const MyPinCreationStateChangedMessage&> m_stateChangeHandler;
                Eegeo::Helpers::TCallback2<MyPinCreationCompositeViewModel, ScreenControl::View::IScreenControlViewModel&, float> m_settingsMenuStateChangedCallback;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                IMyPinCreationInitiationViewModel& m_initiationViewModel;
                IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
                ScreenControl::View::IScreenControlViewModel& m_interiorControlViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_searchMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_settingsMenuViewModel;
                bool m_showUiComponents;
                Eegeo::Helpers::TCallback1<MyPinCreationCompositeViewModel, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                ExampleApp::Watermark::View::IWatermarkViewModel& m_watermarkViewModel;

                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
            };
        }
    }
}
