// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewCLI.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationConfirmationView.h"

namespace ExampleApp
{
    void MyPinCreationViewCLIMethods::StartButtonPressed(System::IntPtr^ nativeObjectPtr)
    {
        ExampleApp::MyPinCreation::View::MyPinCreationInitiationView* pView = reinterpret_cast<ExampleApp::MyPinCreation::View::MyPinCreationInitiationView*>(nativeObjectPtr->ToPointer());
        pView->OnSelected();
    }

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