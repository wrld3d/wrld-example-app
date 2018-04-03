// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mobileexampleapp;

import java.io.IOException;
import java.io.InputStream;

import org.json.JSONException;
import org.json.JSONObject;

import com.eegeo.entrypointinfrastructure.EegeoSurfaceView;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.entrypointinfrastructure.NativeJniCalls;
import com.eegeo.helpers.IRuntimePermissionResultHandler;
import com.eegeo.recce.*;

import android.Manifest;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.support.v4.content.ContextCompat;
import android.util.DisplayMetrics;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.view.View;

import net.hockeyapp.android.CrashManager;
import net.hockeyapp.android.Constants;
import net.hockeyapp.android.CrashManagerListener;
import net.hockeyapp.android.NativeCrashManager;


public class BackgroundThreadActivity extends MainActivity
{
    final public Object screenshotsCompletedLock = new Object();

    private long m_nativeAppWindowPtr;
    private EegeoSurfaceView m_surfaceView;
    private SurfaceHolder m_surfaceHolder;
    private ThreadedUpdateRunner m_threadedRunner;
    private Thread m_updater;
    private String m_hockeyAppId;
    /* The url used if the app is opened by a deep link.
     *  As the app in singleTask this is set in onNewIntent and must be
     *  set to null before for the app pauses.
     */
    private Uri m_deepLinkUrlData;
    private boolean m_rotationInitialised = false;
    private boolean m_locationPermissionRecieved;
    public static final int LOCATION_PERMISSION_REQUEST_CODE = 52;

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

        m_hockeyAppId = readHockeyAppId();
        Constants.loadFromContext(this);
        NativeJniCalls.setUpBreakpad(Constants.FILES_PATH);
        NativeCrashManager.handleDumpFiles(this, m_hockeyAppId);

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
        
        m_rotationInitialised = !setDisplayOrientationBasedOnDeviceProperties();

        setContentView(R.layout.activity_main);


        Intent intent = getIntent();
        if(intent !=null)
        {
            m_deepLinkUrlData = intent.getData();
        }


        m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
        m_surfaceView.getHolder().addCallback(this);
        m_surfaceView.setActivity(this);

        DisplayMetrics dm = getResources().getDisplayMetrics();
        final float dpi = dm.ydpi;
        final int density = dm.densityDpi;
        final Activity activity = this;

        boolean locationPermissionGranted = ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED;
        m_locationPermissionRecieved = locationPermissionGranted;

        getRuntimePermissionDispatcher().addRuntimePermissionResultHandler(new  IRuntimePermissionResultHandler()
        {
            @Override
            public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
            {
                if(requestCode == LOCATION_PERMISSION_REQUEST_CODE)
                {
                    m_locationPermissionRecieved = true;
                }
            }
        });

        this.getRuntimePermissionDispatcher().hasLocationPermissionsWithCode(LOCATION_PERMISSION_REQUEST_CODE);

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
        updateSystemNavigation();
    	if(hasValidHockeyAppId())
    	{
    		registerCrashLogging();
    	}

    }

    @Override
    protected void onPause()
    {
        super.onPause();
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
        if (!checkLocalBackButtonListeners())
        {
            moveTaskToBack(true);
        }
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
                NativeJniCalls.pauseNativeCode();
            }
        });
    }

    @Override
    public void surfaceChanged(final SurfaceHolder holder, int format, int width, int height)
    {
        m_surfaceHolder = holder;
        if (!m_rotationInitialised)
        {
            return;
        }

        runOnNativeThread(new Runnable()
        {
            public void run()
            {
                m_surfaceHolder = holder;
                if(m_surfaceHolder != null)
                {
                    long oldWindow = NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
                    m_threadedRunner.start();
                    releaseNativeWindowDeferred(oldWindow);

                    if(m_deepLinkUrlData != null)
                    {
                        NativeJniCalls.handleUrlOpenEvent(m_deepLinkUrlData.getHost(), m_deepLinkUrlData.getPath(), m_deepLinkUrlData.getEncodedQuery());
                        m_deepLinkUrlData = null;
                    }

                    NativeJniCalls.resumeNativeCode();
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

    @Override
    public void onConfigurationChanged(Configuration newConfiguration)
    {
        super.onConfigurationChanged(newConfiguration);
        m_rotationInitialised = true;
    }

    @Override
    public void onScreenshotsCompleted()
    {
        synchronized (screenshotsCompletedLock)
        {
            screenshotsCompletedLock.notifyAll();
        }
    }

    private boolean setDisplayOrientationBasedOnDeviceProperties()
    {
        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        final int width = displayMetrics.widthPixels;
        final int height = displayMetrics.heightPixels;

    	// Technique based on http://stackoverflow.com/a/9308284 using res/values configuration.
        if(getResources().getBoolean(R.bool.isPhone))
        {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
            final boolean needsRotation = width > height;
            return needsRotation;
        }
        else
        {
        	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
            final boolean needsRotation = width < height;
            return needsRotation;
        }
    }
    
    private String readHockeyAppId()
    {    
        try
        {  
            String applicationConfigurationPath = NativeJniCalls.getAppConfigurationPath();
            InputStream is = getAssets().open(applicationConfigurationPath);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            String jsonStr = new String(buffer, "UTF-8");
            JSONObject json = new JSONObject(jsonStr);
            return json.get("hockey_app_id").toString();
        } catch (IOException e) {
            // Master Ball
        } catch (JSONException e) {
            // Master Ball
        }
        
        return "";
    }
    
    private boolean hasValidHockeyAppId()
    {
    	return m_hockeyAppId.length() == 32;
    }
    private void registerCrashLogging()
    {    
    	CrashManager.register(this, m_hockeyAppId, new CrashManagerListener() {
    		public boolean shouldAutoUploadCrashes() {
    			return true;
    		}
    	});
    }

    private class ThreadedUpdateRunner implements Runnable
    {
        private long m_endOfLastFrameNano;
        private boolean m_running;
        private volatile Handler m_nativeThreadHandler;
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
            while(!m_destroyed)
            {
                SystemClock.sleep(200);
            }
        }

        synchronized void blockUntilThreadHasStoppedUpdatingPlatform()
        {
            while(!m_stoppedUpdatingPlatformBeforeTeardown)
            {
                SystemClock.sleep(200);
            }
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
            Handler tmp = new Handler();
            m_nativeThreadHandler = tmp;

            runOnNativeThread(new Runnable()
            {
                public void run()
                {
                    long timeNowNano = System.nanoTime();
                    long nanoDelta = timeNowNano - m_endOfLastFrameNano;
                    final float deltaSeconds = (float)((double)nanoDelta / 1e9);

                    if(deltaSeconds > m_frameThrottleDelaySeconds)
                    {
                        if(m_running && m_locationPermissionRecieved)
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

    public void releaseNativeWindowDeferred(final long oldWindow)
    {
        runOnNativeThread(new Runnable() {
            @Override
            public void run() {
                NativeJniCalls.releaseNativeWindow(oldWindow);
            }
        });
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        updateSystemNavigation();
    }

    private void updateSystemNavigation()
    {
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN |
                                                         View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
                                                         View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                                                         View.SYSTEM_UI_FLAG_IMMERSIVE);
    }
}
