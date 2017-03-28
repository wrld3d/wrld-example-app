// Copyright eeGeo Ltd (2012-2017), All Rights Reserved
//
package com.eegeo.automation;

public interface AsyncSurfaceScreenshotCompositor
{
    void run(final long width, final long height, final byte[] surfaceScreenshotBytes);
}
