// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "AppModeChangedMessage.h"
#include "VirtualKeyboard.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationController : private Eegeo::NonCopyable
            {
            public:
                MyPinCreationInitiationController(IMyPinCreationInitiationViewModel& viewModel,
                                                  IMyPinCreationInitiationView& view,
                                                  IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                  ExampleAppMessaging::TMessageBus& messageBus,
                                                  Metrics::IMetricsService& metricsService);
                
                ~MyPinCreationInitiationController();

                void OnSelected();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

            private:

                IMyPinCreationInitiationViewModel& m_viewModel;
                IMyPinCreationInitiationView& m_view;
                IMyPinCreationConfirmationViewModel& m_confirmationViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;
                bool m_userInteractionEnabled;
                
                Eegeo::Helpers::TCallback2<MyPinCreationInitiationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationInitiationController> m_selectedCallback;
                Eegeo::Helpers::TCallback1<MyPinCreationInitiationController, const VirtualKeyboard::VirtualKeyboardStateChangedMessage&> m_virtualKeyboardStateChangedMessageHandler;
                
                Eegeo::Helpers::TCallback1<MyPinCreationInitiationController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                Eegeo::Helpers::TCallback1<MyPinCreationInitiationController, const UserInteraction::UserInteractionEnabledChangedMessage&> m_userInteractionEnabledChangedHandler;

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

                void OnVirtualKeyboardStateChangedMessage(const VirtualKeyboard::VirtualKeyboardStateChangedMessage& message);

                void OnUserInteractionEnabledChanged(const UserInteraction::UserInteractionEnabledChangedMessage& message);

                bool m_appModeAllowsOpen;
            };
        }
    }
}
