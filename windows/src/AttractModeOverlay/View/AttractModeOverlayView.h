// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AttractModeStateChangedMessage.h"
#include "BidirectionalBus.h"
#include "IMenuViewModel.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "ReflectionHelpers.h"
#include "VirtualKeyboardView.h"
#include "WindowsNativeState.h"

namespace ExampleApp
{
    namespace AttractModeOverlay
    {
        namespace View
        {
            class AttractModeOverlayView
            {
            public:
                AttractModeOverlayView(WindowsNativeState& nativeState,
                                       ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pVirtualKeyboard,
                                       ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~AttractModeOverlayView();

            private:
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
                void OnAttractModeStateChanged(const AttractMode::AttractModeStateChangedMessage& message);

                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<AttractModeOverlayView, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<AttractModeOverlayView, const AttractMode::AttractModeStateChangedMessage&> m_attractModeStateChangedCallback;

                WindowsNativeState& m_nativeState;

                ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& m_myPinCreationDetailsViewModel;

                ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* m_pVirtualKeyboard;

                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStart;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStop;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeExiting;
                Helpers::ReflectionHelpers::Method<void> mDestroy;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
