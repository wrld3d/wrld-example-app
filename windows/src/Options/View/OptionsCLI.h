// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class OptionsViewCLIMethods
    {
    public:

        static void CloseButtonSelected(System::IntPtr nativeObjectPtr);
        
        static void StreamOverWifiToggled(System::IntPtr nativeObjectPtr);
        
        static void CachingEnabledToggled(System::IntPtr nativeObjectPtr);
        
        static void ClearCacheSelected(System::IntPtr nativeObjectPtr);

        static void ReplayTutorials(System::IntPtr nativeObjectPtr, System::Boolean enableTutorials);
    };
}