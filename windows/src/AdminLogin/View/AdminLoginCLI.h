// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AdminLoginView.h"

namespace ExampleApp
{
    public ref class AdminLoginCLI
    {
    public:
        static void HandleOkClicked(System::IntPtr nativeCallerPointer, System::String^ password);
    };

    namespace AdminLogin
    {
        namespace View
        {
            public ref class ManagedAdminLoginView
            { 
            public:
                ManagedAdminLoginView();
                ~ManagedAdminLoginView();
                !ManagedAdminLoginView();

                void InitNative(System::Type^ uiViewClass, System::Object^ uiView, System::String^ password);
                void HandleOkClicked(System::String^ password);

            private:
                AdminLoginView *m_pAdminLoginView;
            };
        }
    }
}