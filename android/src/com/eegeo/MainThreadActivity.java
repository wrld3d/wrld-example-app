//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo;

import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.SurfaceHolder;

public class MainThreadActivity extends MainActivity
{
	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private NativeUpdateRunner m_nativeRunner;

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		System.loadLibrary("native-activity");

		setContentView(R.layout.activity_main);

		m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);
		m_surfaceView.setActivity(this);

		DisplayMetrics dm = getResources().getDisplayMetrics();
		final float dpi = dm.ydpi;

		m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(this, getAssets(), dpi);

		if(m_nativeAppWindowPtr == 0)
		{
			throw new RuntimeException("Failed to start native code.");
		}

		final Handler handler = new Handler();
		m_nativeRunner = new NativeUpdateRunner(handler, true);
		handler.post(m_nativeRunner);
	}

	public void runOnNativeThread(Runnable runnable)
	{
		runnable.run();
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		NativeJniCalls.resumeNativeCode();

		if(m_surfaceHolder != null)
		{
			NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
		}
	}

	@Override
	protected void onPause()
	{
		NativeJniCalls.pauseNativeCode();
		super.onPause();
	}

	@Override
	protected void onDestroy()
	{
		super.onStop();
		m_nativeRunner.setIsRunning(false);
		NativeJniCalls.destroyNativeCode();
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
		NativeJniCalls.setNativeSurface(null);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		m_surfaceHolder = holder;
		NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
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
				NativeJniCalls.updateNativeCode(deltaSeconds);
				m_endOfLastFrameNano = timeNowNano;
				m_mainThreadHandler.post(this);
			}
		}
	}
}