// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class SearchMenuViewCLIMethods
	{
    public:
        static void PerformedSearchQuery(System::IntPtr nativePointer, System::String^ text);

        static void OnSearchCleared(System::IntPtr nativeCallerPointer);

        static void HandleSearchItemSelected(System::IntPtr nativeCallerPointer, int itemIndex);
	};
}