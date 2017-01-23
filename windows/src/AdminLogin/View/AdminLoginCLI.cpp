// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AdminLoginCLI.h"
#include "AdminLoginView.h"

#include <msclr/marshal_cppstd.h>

namespace ExampleApp
{
    void AdminLoginCLI::HandleOkClicked(System::IntPtr nativeCallerPointer, System::String^ password)
    {
        AdminLogin::View::AdminLoginView *view = (AdminLogin::View::AdminLoginView*)nativeCallerPointer.ToPointer();
        view->HandleOkClicked(msclr::interop::marshal_as<std::string>(password));
    }

    namespace AdminLogin
    {
        namespace View
        {
            ManagedAdminLoginView::ManagedAdminLoginView()
            {
            }

            ManagedAdminLoginView::~ManagedAdminLoginView()
            {
                Eegeo_DELETE(m_pAdminLoginView);
            }

            ManagedAdminLoginView::!ManagedAdminLoginView()
            {
                Eegeo_DELETE(m_pAdminLoginView);
            }

            void ManagedAdminLoginView::InitNative(System::Type^ uiViewClass, System::Object^ uiView, System::String^ password)
            {
                m_pAdminLoginView = Eegeo_NEW(AdminLoginView)(uiViewClass, uiView, password);
            }

            void ManagedAdminLoginView::HandleOkClicked(System::String^ password)
            {
                msclr::interop::marshal_context context;
                m_pAdminLoginView->HandleOkClicked(context.marshal_as<std::string>(password));
            }
        }
    }
}