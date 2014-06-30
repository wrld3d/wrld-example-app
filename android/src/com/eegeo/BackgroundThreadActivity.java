//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.view.SurfaceHolder;
import android.app.Activity;

public class BackgroundThreadActivity extends MainActivity
{
	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private ThreadedUpdateRunner m_threadedRunner;
	private Thread m_updater;

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
		final Activity activity = this;

		m_threadedRunner = new ThreadedUpdateRunner(false);
		m_updater = new Thread(m_threadedRunner);
		m_updater.start();

		m_threadedRunner.blockUntilThreadStartedRunning();

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(activity, getAssets(), dpi);

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
			}
		});

		if(m_surfaceHolder != null)
		{
			runOnNativeThread(new Runnable()
			{
				public void run()
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
				}
			});
		}
	}

	@Override
	protected void onPause()
	{
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				NativeJniCalls.pauseNativeCode();
			}
		});
		super.onPause();
	}

	@Override
	protected void onDestroy()
	{
		super.onStop();

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
				NativeJniCalls.destroyNativeCode();
			}
		});
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

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
				NativeJniCalls.setNativeSurface(null);
			}
		});
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		m_surfaceHolder = holder;

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
				m_threadedRunner.start();
			}
		});
	}

	private class ThreadedUpdateRunner implements Runnable
	{
		private long m_endOfLastFrameNano;
		private boolean m_running;
		private Handler m_nativeThreadHandler;

		public ThreadedUpdateRunner(boolean running)
		{
			m_endOfLastFrameNano = System.nanoTime();
			m_running = false;
		}

		synchronized void blockUntilThreadStartedRunning()
		{
			while(m_nativeThreadHandler == null);
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

		public void run()
		{
			Looper.prepare();
			m_nativeThreadHandler = new Handler();

			while(true)
			{
				runOnNativeThread(new Runnable()
				{
					public void run()
					{
						long timeNowNano = System.nanoTime();
						if(m_running)
						{
							long nanoDelta = timeNowNano - m_endOfLastFrameNano;
							float deltaSeconds = (float)((double)nanoDelta / 1e9);
							NativeJniCalls.updateNativeCode(deltaSeconds);
						}
						m_endOfLastFrameNano = timeNowNano;
						runOnNativeThread(this);
					}
				});

				Looper.loop();
			}
		}
	}
}