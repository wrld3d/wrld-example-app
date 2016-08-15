// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.web;

public class ConnectivityServiceJniMethods
{
	public static native void SetConnectivityType(long nativeCallerPointer, int connectivityType, String wifiSSID);
}
