// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class SearchResultPoiViewCLI
    {
    public:
        static void CloseButtonClicked(System::IntPtr nativeCallerPointer);
        static void TogglePinnedButtonClicked(System::IntPtr nativeCallerPointer);
    };
}