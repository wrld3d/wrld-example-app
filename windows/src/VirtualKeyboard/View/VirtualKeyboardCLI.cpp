// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VirtualKeyboardCLI.h"
#include "VirtualKeyboardView.h"

namespace ExampleApp
{
    void VirtualKeyboardCLIMethods::OnVisibilityChanged(System::IntPtr^ nativeObjectPtr, bool isVisible)
    {
        ExampleApp::VirtualKeyboard::View::VirtualKeyboardView* pView = reinterpret_cast<ExampleApp::VirtualKeyboard::View::VirtualKeyboardView*>(nativeObjectPtr->ToPointer());
        pView->OnVisibilityChanged(isVisible);
    }
}
