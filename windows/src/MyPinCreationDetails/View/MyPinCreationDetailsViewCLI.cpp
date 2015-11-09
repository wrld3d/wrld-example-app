// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewCLI.h"

namespace ExampleApp
{
    void MyPinCreationDetailsViewCLI::CloseButtonPressed(System::IntPtr nativeCallerPointer)
    {
        MyPinCreationDetails::View::MyPinCreationDetailsView *view = (MyPinCreationDetails::View::MyPinCreationDetailsView*)nativeCallerPointer.ToPointer();
        view->OnDismissed();
    }

    void MyPinCreationDetailsViewCLI::SubmitButtonpressed(System::IntPtr nativeCallerPointer)
    {
        MyPinCreationDetails::View::MyPinCreationDetailsView *view = (MyPinCreationDetails::View::MyPinCreationDetailsView*)nativeCallerPointer.ToPointer();
        view->OnConfirmed();
    }
}



