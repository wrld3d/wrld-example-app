// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ReflectionHelpers.h"
#include "WindowsNativeState.h"

namespace ExampleApp
{
    namespace VirtualKeyboard
    {
        namespace View
        {
            class VirtualKeyboardView
            {
            public:
                VirtualKeyboardView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
                ~VirtualKeyboardView();

				void AddCustomKeyboardLayout(std::vector<std::vector<std::string>>);
                void OnVisibilityChanged(const bool isVisible);
                void HideVirtualKeyboard();

            private:
                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mHideVirtualKeyboard;
				Helpers::ReflectionHelpers::Method<System::String^, System::String^, System::String^, System::String^> mAddCustomKeyboardKey;
				Helpers::ReflectionHelpers::Method<void> mClearCustomKeyboardKeys;

                ExampleAppMessaging::TMessageBus& m_messageBus;

                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
