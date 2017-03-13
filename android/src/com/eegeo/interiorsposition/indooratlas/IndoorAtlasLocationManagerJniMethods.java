// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.interiorsposition.indooratlas;

public class IndoorAtlasLocationManagerJniMethods
{
    public static native void DidUpdateLocation(long nativeCallerPointer,
                                                double latitude,
                                                double longitude,
                                                String floorId);

    public static native void SetIsAuthorized(long nativeCallerPointer, boolean isAuthorized);
}
