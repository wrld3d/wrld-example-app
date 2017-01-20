// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AdminLoginView.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace AdminLogin
    {
        namespace View
        {
            AdminLoginView::AdminLoginView(WindowsNativeState& nativeState, const std::string& adminPassword)
                : m_nativeState(nativeState)
                , m_adminPassword(adminPassword)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.AdminLoginView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mOnPasswordAccepted.SetupMethod(m_uiViewClass, m_uiView, "OnPasswordAccepted");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
            }

            AdminLoginView::~AdminLoginView()
            {
                mDestroy();
            }

            void AdminLoginView::HandleOkClicked(const std::string password)
            {
                mOnPasswordAccepted(password == m_adminPassword);
            }
        }
    }
}
