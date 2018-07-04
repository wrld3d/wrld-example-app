package com.eegeo.mapapi;

//import android.support.annotation.UiThread;

/* This interface's fully-qualified type name must
 marry up with the location of the android api java interface */
public interface INativeMessageRunner
{
    //@UiThread
    void runOnNativeThread(Runnable runnable);
}
