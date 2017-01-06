// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

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
                                       ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                       ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                       ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pVirtualKeyboard,
                                       ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~AttractModeOverlayView();

            private:
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<AttractModeOverlayView, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;

                WindowsNativeState& m_nativeState;

                ExampleApp::Menu::View::IMenuViewModel& m_searchMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_settingsMenuViewModel;
                ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& m_myPinCreationDetailsViewModel;

                ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* m_pVirtualKeyboard;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStart;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStop;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
