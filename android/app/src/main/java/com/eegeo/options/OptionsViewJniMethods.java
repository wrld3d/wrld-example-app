//Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.options;

public class OptionsViewJniMethods 
{
	 public static native void CloseButtonSelected(long nativeCallerPointer);
	 
	 public static native void StreamOverWifiToggled(long nativeCallerPointer);
	 
	 public static native void CachingEnabledToggled(long nativeCallerPointer);
	 
	 public static native void ClearCacheSelected(long nativeCallerPointer);
}