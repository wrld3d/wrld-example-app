package com.eegeo.location;

public class HeadingServiceJniMethods
{
    public static native void UpdateHeading(long nativeCallerPointer, double headingDegrees);
}
