// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.automation;

public class AlbumScreenshotServiceJniMethods
{
    public static native void AsyncSurfaceScreenshot(long nativeCallerPointer, AsyncSurfaceScreenshotCompositor compositor);
}
