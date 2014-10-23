package com.eegeo.menu;

public class MenuViewJniMethods 
{
	public static native void ViewClicked(long nativeCallerPointer);
	
	public static native void ViewOpenCompleted(long nativeCallerPointer);
	
	public static native void ViewCloseCompleted(long nativeCallerPointer);
	
	public static native void ViewDragStarted(long nativeCallerPointer);
	
	public static native void ViewDragInProgress(long nativeCallerPointer, float normalisedDragState);
	
	public static native void ViewDragCompleted(long nativeCallerPointer);

	public static native void SelectedItem(long nativeCallerPointer, String selectedItem, int index);

	public static native boolean TryBeginDrag(long nativeCallerPointer);
}
