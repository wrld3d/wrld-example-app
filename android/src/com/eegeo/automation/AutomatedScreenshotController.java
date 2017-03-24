// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.automation;

import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;

public class AutomatedScreenshotController
{
    private MainActivity m_activity;
    private long m_nativeCallerPointer;

    public AutomatedScreenshotController(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    public void onScreenshotsCompleted()
    {
        m_activity.onScreenshotsCompleted();
    }
}
