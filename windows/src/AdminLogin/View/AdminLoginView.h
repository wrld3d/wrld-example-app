// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ReflectionHelpers.h"
#include "WindowsNativeState.h"

namespace ExampleApp
{
    namespace AdminLogin
    {
        namespace View
        {
            class AdminLoginView
            {
            public:
                AdminLoginView(WindowsNativeState& nativeState, const std::string& adminPassword);
                ~AdminLoginView();

                void HandleOkClicked(const std::string password);

            private:
                WindowsNativeState& m_nativeState;

                std::string m_adminPassword;

                Helpers::ReflectionHelpers::Method<bool> mOnPasswordAccepted;
                Helpers::ReflectionHelpers::Method<void> mDismiss;
                Helpers::ReflectionHelpers::Method<void> mDestroy;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
