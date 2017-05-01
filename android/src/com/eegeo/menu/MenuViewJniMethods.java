// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

public class MenuViewJniMethods
{
    public static native void ViewClicked(long nativeCallerPointer);

    public static native void ViewOpenStarted(long nativeCallerPointer);

    public static native void ViewOpenCompleted(long nativeCallerPointer);

    public static native void ViewCloseCompleted(long nativeCallerPointer);

    public static native void ViewDragStarted(long nativeCallerPointer);

    public static native void ViewDragInProgress(long nativeCallerPointer, float normalisedDragState);

    public static native void ViewDragCompleted(long nativeCallerPointer);

    public static native void SelectedItem(long nativeCallerPointer, int sectionIndex, int itemIndex);

    public static native boolean TryBeginDrag(long nativeCallerPointer);
}
