package com.eegeo.navwidget;

public class NavWidgetViewJniMethods
{
    public static native void CloseButtonClicked(long nativeCallerPointer);

    public static native void SelectStartLocationClicked(long nativeCallerPointer);

    public static native void SelectEndLocationClicked(long nativeCallerPointer);

    public static native void StartLocationClearButtonClicked(long nativeCallerPointer);

    public static native void EndLocationClearButtonClicked(long nativeCallerPointer);

    public static native void StartEndLocationsSwapped(long nativeCallerPointer);
}
