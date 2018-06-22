package com.eegeo.location;

public class LocationServiceJniMethods
{
    public static native void UpdateLocation(
            long nativeCallerPointer,
            double latitudeDegrees,
            double longitudeDegrees,
            double altitudeMeters,
            double horizontalAccuracyMeters);

    public static native void UpdateAuthorized(
            long nativeCallerPointer,
            boolean isAuthorized);
}
