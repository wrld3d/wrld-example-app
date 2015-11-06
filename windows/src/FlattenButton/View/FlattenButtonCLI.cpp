// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonCLI.h"
#include "FlattenButtonView.h"

namespace ExampleApp
{
    void FlattenButtonViewCLIMethods::OnToggle(System::IntPtr nativeCallerPointer, bool flattened)
    {
        FlattenButton::View::FlattenButtonView *view = (FlattenButton::View::FlattenButtonView*)nativeCallerPointer.ToPointer();
        view->OnToggle(flattened);
    }
}
