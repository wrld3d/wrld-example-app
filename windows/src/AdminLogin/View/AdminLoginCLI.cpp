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
}