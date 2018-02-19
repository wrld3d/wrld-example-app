// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewCLI.h"
#include "MyPinCreationConfirmationView.h"

namespace ExampleApp
{
   
    void MyPinCreationViewCLIMethods::ConfirmationCancelButtonPressed(System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView*>(nativeObjectPtr->ToPointer());
        pView->OnDismissed();
    }

    void MyPinCreationViewCLIMethods::ConfirmationOkButtonPressed(System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationConfirmationView*>(nativeObjectPtr->ToPointer());
        pView->OnConfirmed();
    }
}