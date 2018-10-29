// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

public class SearchResultPoiViewJniMethods
{
    public static native void CloseButtonClicked(long nativeCallerPointer);

    public static native void TogglePinnedButtonClicked(long nativeCallerPointer);

    public static native void DirectionsButtonClicked(long nativeCallerPointer);

    public static native boolean isJavascriptWhitelisted(long nativeCallerPointer, String url);
}
