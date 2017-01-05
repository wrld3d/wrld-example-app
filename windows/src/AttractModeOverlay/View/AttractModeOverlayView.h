// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

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
                                       AppModes::SdkModel::IAppModeModel& appModeModel,
                                       ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                       ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                       ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pVirtualKeyboard,
                                       ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel);
                ~AttractModeOverlayView();

            private:
                void OnAppModeChanged();

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStart;
                Helpers::ReflectionHelpers::Method<void> mOnAttractModeStop;

                AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Helpers::TCallback0<AttractModeOverlayView> m_appModeChangedCallback;

                ExampleApp::Menu::View::IMenuViewModel& m_searchMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_settingsMenuViewModel;
                ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& m_myPinCreationDetailsViewModel;

                ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* m_pVirtualKeyboard;

                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
