package com.eegeo.poicreationdetails;

public class PoiCreationDetailsJniMethods 
{
		public static native void CloseButtonPressed(long nativeCallerPointer);
		public static native void SubmitButtonPressed(long nativeCallerPointer, String title, String description, String imagePath, boolean shouldShare);
}
