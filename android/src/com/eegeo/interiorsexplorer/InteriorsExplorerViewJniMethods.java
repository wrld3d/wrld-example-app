// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.interiorsexplorer;

public class InteriorsExplorerViewJniMethods
{
    public static native void OnDismissedClicked(long nativeCallerPointer);
    public static native void OnFloorSelected(long nativeCallerPointer, int selectedFloor);
}
