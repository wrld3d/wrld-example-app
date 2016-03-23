// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class InteriorsExplorerCLIMethods
    {
    public:

        static void Dismiss(System::IntPtr nativeObjectPtr);

        static void SelectFloor(System::IntPtr nativeObjectPtr, int index);

        static void SetFloorSelectionDrag(System::IntPtr nativeObjectPtr, System::Double dragParam);
    };
};