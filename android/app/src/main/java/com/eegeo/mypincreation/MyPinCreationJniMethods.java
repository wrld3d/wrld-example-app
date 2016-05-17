// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mypincreation;

public class MyPinCreationJniMethods
{
    public static native void StartButtonPressed(long nativeCallerPointer);
    public static native void ConfirmationCancelButtonPressed(long nativeCallerPointer);
    public static native void ConfirmationOkButtonPressed(long nativeCallerPointer);
}
