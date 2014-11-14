package com.eegeo.mypincreation;

public class MyPinCreationJniMethods 
{
	public static native void StartButtonPressed(long nativeCallerPointer);
	public static native void ConfirmationCancelButtonPressed(long nativeCallerPointer);
	public static native void ConfirmationOkButtonPressed(long nativeCallerPointer);
}
