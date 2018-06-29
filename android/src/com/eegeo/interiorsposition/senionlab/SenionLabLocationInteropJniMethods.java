package com.eegeo.interiorsposition.senionlab;

public class SenionLabLocationInteropJniMethods {
    public static native void UpdateIsAuthorized(long nativeCallerPointer, boolean isAuthorized);

    public static native void UpdateLocation(long nativeCallerPointer,
                                             double latitudeDegrees,
                                             double longitudeDegrees,
                                             double horizontalAccuracyInMeters,
                                             int senionFloorNumber);

    public static native void UpdateHeading(long nativeCallerPointer, double heading);
}