// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.interiorsposition.senionlab;

public class SenionLabBroadcastReceiverJniMethods
{
    public static native void DidUpdateLocation(long nativeCallerPointer,
                                                double latitude,
                                                double longitude,
                                                int floorNumber);

    public static native void SetIsAuthorized(long nativeCallerPointer, boolean isAuthorized);
}
