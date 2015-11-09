// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassCLI.h"
#include "CompassView.h"

namespace ExampleApp
{
    void CompassViewCLIMethods::HandleClick(System::IntPtr nativeCallerPointer)
    {
        Compass::View::CompassView *view = (Compass::View::CompassView*)nativeCallerPointer.ToPointer();
        view->OnCycle();
    }
}