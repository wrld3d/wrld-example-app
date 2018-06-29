// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.interiorsposition.indooratlas;

public class IndoorAtlasLocationInteropJniMethods
{
    public static native void UpdateLocation(long nativeCallerPointer,
                                             double latitudeInDegrees,
                                             double longitudeInDegrees,
                                             double horizontalAccuracyInMeters,
                                             String floorId);

    public static native void UpdateIsAuthorized(long nativeCallerPointer, boolean isAuthorized);
}
