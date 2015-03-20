// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.entrypointinfrastructure;

public interface INativeMessageRunner
{
    void runOnNativeThread(Runnable runnable);
}
