// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    public ref class MenuViewCLIMethods
    {
    public:
        static void ViewClicked(
            System::IntPtr^ nativeObjectPtr);

        static void ViewOpenCompleted(
            System::IntPtr^ nativeObjectPtr);

        static void ViewOpenStarted(
            System::IntPtr^ nativeObjectPtr);

        static void ViewCloseCompleted(
            System::IntPtr^ nativeObjectPtr);

        static void ViewDragStarted(
            System::IntPtr^ nativeObjectPtr);

        static void ViewDragInProgress(
            System::IntPtr^ nativeObjectPtr,
            float normalisedDragState);

        static void ViewDragCompleted(
            System::IntPtr^ nativeObjectPtr);

        static void SelectedItem(
            System::IntPtr^ nativeObjectPtr,
            int sectionIndex,
            int itemIndex);

        static bool TryBeginDrag(
            System::IntPtr^ nativeObjectPtr);
    };
};
