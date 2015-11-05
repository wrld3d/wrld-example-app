// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class MyPinCreationViewCLIMethods
    {
    public:
        static void StartButtonPressed(System::IntPtr^ nativeObjectPtr);

        static void ConfirmationCancelButtonPressed(System::IntPtr^ nativeObjectPtr);

        static void ConfirmationOkButtonPressed(System::IntPtr^ nativeObjectPtr);
    };
};