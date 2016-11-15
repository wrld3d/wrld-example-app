// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mobileexampleapp;

import com.eegeo.entrypointinfrastructure.EegeoSurfaceView;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.entrypointinfrastructure.NativeJniCalls;
import com.eegeo.mobileexampleapp.R;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.util.DisplayMetrics;
import android.view.SurfaceHolder;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;


public class BackgroundThreadActivity extends MainActivity
{
    private EegeoSurfaceView m_surfaceView;
    private SurfaceHolder m_surfaceHolder;
    private long m_nativeAppWindowPtr;
    private ThreadedUpdateRunner m_threadedRunner;
    private Thread m_updater;
    /* The url used if the app is opened by a deep link.
     *  As the app in singleTask this is set in onNewIntent and must be
     *  set to null before for the app pauses.
     */
    private Uri m_deepLinkUrlData;

    static
    {
        System.loadLibrary("eegeo-mobile-example-app");
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        if ((getIntent().getFlags() & Intent.FLAG_ACTIVITY_BROUGHT_TO_FRONT) != 0)
        {
            finish();
            return;
        }
        
        PackageInfo pInfo = null;
        try 
        {
        	pInfo = getPackageManager().getPackageInfo(getPackageName(), 0);
        } 
        catch (NameNotFoundException e) 
        {
        	e.printStackTrace();
        }
        final String versionName = pInfo.versionName;
        final int versionCode = pInfo.versionCode;
        
        setDisplayOrientationBasedOnDeviceProperties();

        setContentView(R.layout.activity_main);

        m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
        m_surfaceView.getHolder().addCallback(this);
        m_surfaceView.setActivity(this);

        DisplayMetrics dm = getResources().getDisplayMetrics();
        final float dpi = dm.ydpi;
        final int density = dm.densityDpi;
        final Activity activity = this;

        m_threadedRunner = new ThreadedUpdateRunner(false);
        m_updater = new Thread(m_threadedRunner);
        m_updater.start();

        m_threadedRunner.blockUntilThreadStartedRunning();

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(activity, getAssets(), dpi, density, versionName, versionCode);
                
                if(m_nativeAppWindowPtr == 0)
                {
                    throw new RuntimeException("Failed to start native code.");
                }
            }
        });
    }

    public void runOnNativeThread(Runnable runnable)
    {
        m_threadedRunner.postTo(runnable);
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                NativeJniCalls.resumeNativeCode();
                m_threadedRunner.start();

                if(m_surfaceHolder != null && m_surfaceHolder.getSurface() != null)
                {
                    NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
                }

                if(m_deepLinkUrlData != null) {
                    NativeJniCalls.handleUrlOpenEvent(m_deepLinkUrlData.getHost(), m_deepLinkUrlData.getPath());
                }
            }
        });
    }

    @Override
    protected void onPause()
    {
        super.onPause();

        m_deepLinkUrlData = null;

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_threadedRunner.stop();
                NativeJniCalls.pauseNativeCode();
            }
        });
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();

        if (m_threadedRunner == null)
        {
            return;
        }

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                NativeJniCalls.stopUpdatingNativeCode();
                m_threadedRunner.flagUpdatingNativeCodeStopped();
            }
        });

        m_threadedRunner.blockUntilThreadHasStoppedUpdatingPlatform();

        NativeJniCalls.destroyApplicationUi();

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_threadedRunner.stop();
                NativeJniCalls.destroyNativeCode();
                m_threadedRunner.destroyed();
            }
        });

        m_threadedRunner.blockUntilThreadHasDestroyedPlatform();

        m_nativeAppWindowPtr = 0;
    }

    @Override
    public void onBackPressed()
    {
        moveTaskToBack(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder)
    {
        //nothing to do
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {
        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_threadedRunner.stop();
            }
        });
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    {
        final SurfaceHolder h = holder;

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_surfaceHolder = h;
                if(m_surfaceHolder != null)
                {
                    NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
                    m_threadedRunner.start();
                }
            }
        });
    }
    
    @Override
    public void onNewIntent(Intent intent) {
         m_deepLinkUrlData = intent.getData();

    }

    public void dispatchRevealUiMessageToUiThreadFromNativeThread(final long nativeCallerPointer)
    {
        runOnUiThread(new Runnable()
        {
            public void run()
            {
                NativeJniCalls.revealApplicationUi(nativeCallerPointer);
            }
        });
    }

    public void dispatchUiCreatedMessageToNativeThreadFromUiThread(final long nativeCallerPointer)
    {
        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                NativeJniCalls.handleApplicationUiCreatedOnNativeThread(nativeCallerPointer);
            }
        });
    }
    
    private void setDisplayOrientationBasedOnDeviceProperties()
    {
    	// Technique based on http://stackoverflow.com/a/9308284 using res/values configuration.
        if(getResources().getBoolean(R.bool.isPhone))
        {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
        }
        else
        {
        	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
        }
    }

    private class ThreadedUpdateRunner implements Runnable
    {
        private long m_endOfLastFrameNano;
        private boolean m_running;
        private Handler m_nativeThreadHandler;
        private float m_frameThrottleDelaySeconds;
        private boolean m_destroyed;
        private boolean m_stoppedUpdatingPlatformBeforeTeardown;

        public ThreadedUpdateRunner(boolean running)
        {
            m_endOfLastFrameNano = System.nanoTime();
            m_running = false;
            m_destroyed = false;
            m_stoppedUpdatingPlatformBeforeTeardown = false;

            float targetFramesPerSecond = 30.f;
            m_frameThrottleDelaySeconds = 1.f/targetFramesPerSecond;
        }

        synchronized void blockUntilThreadStartedRunning()
        {
            while(m_nativeThreadHandler == null);
        }

        synchronized void blockUntilThreadHasDestroyedPlatform()
        {
            while(!m_destroyed);
        }

        synchronized void blockUntilThreadHasStoppedUpdatingPlatform()
        {
            while(!m_stoppedUpdatingPlatformBeforeTeardown);
        }

        public void postTo(Runnable runnable)
        {
            m_nativeThreadHandler.post(runnable);
        }

        public void start()
        {
            m_running = true;
        }

        public void stop()
        {
            m_running = false;
        }

        public void destroyed()
        {
            m_destroyed = true;
        }

        void flagUpdatingNativeCodeStopped()
        {
            m_stoppedUpdatingPlatformBeforeTeardown = true;
        }

        public void run()
        {
            Looper.prepare();
            m_nativeThreadHandler = new Handler();

            runOnNativeThread(new Runnable()
            {
                public void run()
                {
                    long timeNowNano = System.nanoTime();
                    long nanoDelta = timeNowNano - m_endOfLastFrameNano;
                    final float deltaSeconds = (float)((double)nanoDelta / 1e9);

                    if(deltaSeconds > m_frameThrottleDelaySeconds)
                    {
                        if(m_running)
                        {
                            NativeJniCalls.updateNativeCode(deltaSeconds);

                            runOnUiThread(new Runnable()
                            {
                                public void run()
                                {
                                    NativeJniCalls.updateUiViewCode(deltaSeconds);
                                }
                            });
                        }
                        else
                        {
                            SystemClock.sleep(200);
                        }

                        m_endOfLastFrameNano = timeNowNano;
                    }

                    runOnNativeThread(this);
                }
            });

            Looper.loop();
        }
    }
}
