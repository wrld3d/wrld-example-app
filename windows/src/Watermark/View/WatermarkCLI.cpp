// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkCLI.h"
#include "WatermarkView.h"

namespace ExampleApp
{
    void WatermarkCLI::OnSelected(System::IntPtr^ nativeObjectPointer)
    {
        Watermark::View::WatermarkView* view = reinterpret_cast<Watermark::View::WatermarkView*>(nativeObjectPointer->ToPointer());
        view->OnSelected();
    }
}