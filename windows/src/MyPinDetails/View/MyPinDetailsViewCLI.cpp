// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewCLI.h"
#include "MyPinDetailsView.h"

namespace ExampleApp
{
    void MyPinDetailsViewCLI::CloseButtonClicked(System::IntPtr nativePointer)
    {
        MyPinDetails::View::MyPinDetailsView* pView = reinterpret_cast<MyPinDetails::View::MyPinDetailsView*>(nativePointer.ToPointer());
        pView->OnDismiss();
    }

    void MyPinDetailsViewCLI::RemovePinButtonClicked(System::IntPtr nativePointer)
    {
        MyPinDetails::View::MyPinDetailsView* pView = reinterpret_cast<MyPinDetails::View::MyPinDetailsView*>(nativePointer.ToPointer());
        pView->OnRemove();
    }
}