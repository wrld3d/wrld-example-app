// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

public class SearchMenuViewJniMethods
{
    public static native void SelectedItem(long nativeCallerPointer, int itemIndex);
    
    public static native void PerformSearchQuery(long nativeCallerPointer, String searchQuery);
    
    public static native void OnSearchCleared(long nativeCallerPointer);
}
