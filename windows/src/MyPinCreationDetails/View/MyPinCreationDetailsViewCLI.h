// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreationDetailsView.h"

namespace ExampleApp
{
    public ref class MyPinCreationDetailsViewCLI
    {
    public:
        static void CloseButtonPressed(System::IntPtr nativeCallerPointer);
        static void SubmitButtonpressed(System::IntPtr nativeCallerPointer);
    };

}