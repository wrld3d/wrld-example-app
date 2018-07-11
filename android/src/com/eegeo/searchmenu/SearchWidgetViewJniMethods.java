// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchmenu;

public class SearchWidgetViewJniMethods
{
	public static native void OnSearchResultsCleared(long nativeCallerPointer);
	public static native void OnSearchResultSelected(long nativeCallerPointer, int index);
	public static native void OnSearchResultNavigationRequest(long nativeCallerPointer, int index);
	public static native void OnSearchbarTextChanged(long nativeCallerPointer, String newText);
	public static native void SelectedItem(long nativeCallerPointer, String text, int sectionIndex, int itemIndex);
	public static native void ViewPushesControlsOffscreen(long nativeCallerPointer);
	public static native void ViewAllowsControlsOnscreen(long nativeCallerPointer);
}
