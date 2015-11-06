// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapCLI.h"
#include "WorldPinOnMapView.h"

namespace ExampleApp
{
    void WorldPinOnMapCLI::OnSelected(System::IntPtr nativeCallerPointer)
    {
        WorldPins::View::WorldPinOnMapView *view = (WorldPins::View::WorldPinOnMapView*)nativeCallerPointer.ToPointer();
        view->OnSelected();
    }
}