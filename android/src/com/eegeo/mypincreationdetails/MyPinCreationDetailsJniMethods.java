package com.eegeo.mypincreationdetails;

public class MyPinCreationDetailsJniMethods 
{
		public static native void CloseButtonPressed(long nativeCallerPointer);
		public static native void SubmitButtonPressed(long nativeCallerPointer, String title, String description, String imagePath, byte[] imageData, boolean shouldShare);
}
