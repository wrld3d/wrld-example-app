// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AdminLoginView.h"
#include "ReflectionHelpers.h"

#include <msclr/marshal_cppstd.h>

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace AdminLogin
    {
        namespace View
        {
            AdminLoginView::AdminLoginView(System::Type^ uiViewClass, System::Object^ uiView, System::String^ password)
                : m_uiViewClass(uiViewClass)
                , m_uiView(uiView)
                , m_ownManagedState(false)
            {
                msclr::interop::marshal_context context;
                m_adminPassword = context.marshal_as<std::string>(password);

                InitManagedCalls();
            }

            AdminLoginView::AdminLoginView(const std::string& adminPassword)
                : m_adminPassword(adminPassword)
                , m_ownManagedState(true)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.AdminLoginView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                InitManagedCalls();
            }

            AdminLoginView::~AdminLoginView()
            {
                if (m_ownManagedState)
                {
                    mDestroy();
                }
            }

            void AdminLoginView::HandleOkClicked(const std::string password)
            {
                mOnPasswordAccepted(password == m_adminPassword);
            }

            void AdminLoginView::InitManagedCalls()
            {
                mOnPasswordAccepted.SetupMethod(m_uiViewClass, m_uiView, "OnPasswordAccepted");
                mDismiss.SetupMethod(m_uiViewClass, m_uiView, "Dismiss");
                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
            }
        }
    }
}
