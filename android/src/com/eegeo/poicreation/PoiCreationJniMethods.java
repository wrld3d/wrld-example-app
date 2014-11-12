package com.eegeo.poicreation;

public class PoiCreationJniMethods 
{
	public static native void StartButtonPressed(long nativeCallerPointer);
	public static native void ConfirmationCancelButtonPressed(long nativeCallerPointer);
	public static native void ConfirmationOkButtonPressed(long nativeCallerPointer);
}
