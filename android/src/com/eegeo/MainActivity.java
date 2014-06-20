// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo;

import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.app.Activity;
import android.content.res.AssetManager;

public class MainActivity extends Activity implements SurfaceHolder.Callback
{
	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private NativeUpdateRunner m_nativeRunner;

	public static native long createNativeCode(MainActivity activity, AssetManager assetManager, float dpi);
	public static native void destroyNativeCode();
	public static native void pauseNativeCode();
	public static native void resumeNativeCode();
	public static native void setNativeSurface(Surface surface);
	public static native void updateNativeCode(float deltaTimeSeconds);

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		System.loadLibrary("native-activity");

		setContentView(R.layout.activity_main);

		m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);

		DisplayMetrics dm = getResources().getDisplayMetrics();
		float dpi = dm.ydpi;

		m_nativeAppWindowPtr = createNativeCode(this, getAssets(), dpi);

		if(m_nativeAppWindowPtr == 0)
		{
			throw new RuntimeException("Failed to start native code.");
		}

		final Handler handler = new Handler();
		m_nativeRunner = new NativeUpdateRunner(handler, true);
		handler.post(m_nativeRunner);
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		resumeNativeCode();

		if(m_surfaceHolder != null)
		{
			setNativeSurface(m_surfaceHolder.getSurface());
		}
	}

	@Override
	protected void onPause()
	{
		pauseNativeCode();
		super.onPause();
	}

	@Override
	protected void onDestroy()
	{
		super.onStop();
		m_nativeRunner.setIsRunning(false);
		destroyNativeCode();
		m_nativeAppWindowPtr = 0;
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder)
	{
		//nothing to do
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder)
	{
		m_surfaceHolder = null;
		setNativeSurface(null);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		m_surfaceHolder = holder;
		setNativeSurface(m_surfaceHolder.getSurface());
	}

	private class NativeUpdateRunner implements Runnable
	{
		private long m_endOfLastFrameNano;
		private Handler m_mainThreadHandler;
		private boolean m_running;

		public NativeUpdateRunner(Handler mainThreadHandler, boolean running)
		{
			m_endOfLastFrameNano = System.nanoTime();
			m_mainThreadHandler = mainThreadHandler;
			m_running = running;
		}

		public void setIsRunning(boolean running)
		{
			m_running = running;
		}

		public void run()
		{
			if(m_running)
			{
				long timeNowNano = System.nanoTime();
				long nanoDelta = timeNowNano - m_endOfLastFrameNano;
				float deltaSeconds = (float)((double)nanoDelta / 1e9);
				updateNativeCode(deltaSeconds);
				m_endOfLastFrameNano = timeNowNano;
				m_mainThreadHandler.post(this);
			}
		}
	}
}