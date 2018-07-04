package com.eegeo.location;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Looper;
import android.view.OrientationEventListener;
import android.view.Surface;
import android.view.WindowManager;

import com.eegeo.mapapi.INativeMessageRunner;

@SuppressWarnings("unused")
public class HeadingService implements SensorEventListener {
	private final int m_ctorThreadId;

	private final long m_nativeCallerPointer;
	private Context m_context;
	private final INativeMessageRunner m_nativeMessageRunner;

	private boolean m_listeningForUpdates = false;
	private int m_deviceRotation;

	private SensorManager m_sensorManager;
	private OrientationEventListener m_orientationEventListener = null;

	// The results from SensorManager.getOrientation appear to be worse than the results of
	// the deprecated Sensor.TYPE_ORIENTATION on the test device. To enable SensorManager.getOrientation
	// using the results of the Sensor.TYPE_GRAVITY and Sensor.TYPE_MAGNETIC_FIELD sensors, set
	// this field to false. The results of this have high jitter, so a low-pass filter is used. Even
	// then, the results appear to be inferior to Sensor.TYPE_ORIENTATION.
	private float m_azimuthDegrees = 0.f;

	private double heading() {
		return m_azimuthDegrees;
	}

	private static int getThreadId() {
		return android.os.Process.myTid();
	}

	private void throwIfCalledOnIncorrectThread() {
		final int currentThreadId = getThreadId();

		if (getThreadId() != m_ctorThreadId) {
			final boolean isThisThreadUiThread = (Looper.getMainLooper().getThread() == Thread.currentThread());

			throw new IllegalThreadStateException(
					"heading update was not called on a consistent thread. ctor was called on thread with id '" +
							m_ctorThreadId + "', but the current thread has id '" + currentThreadId + "'" + ". Is current thread the ui thread? : " + isThisThreadUiThread);
		}
	}

	@SuppressWarnings("unused")
	public HeadingService(Context context,
						  INativeMessageRunner nativeMessageRunner,
						  long nativeCallerPointer) {
		//noinspection ConstantConditions -- this doesn't actually throw when it's null
		if(context == null) {
			throw new NullPointerException("context");
		}

		//noinspection ConstantConditions -- this doesn't actually throw when it's null
		if(nativeMessageRunner == null) {
			throw new NullPointerException("nativeMessageRunner");
		}

		m_context = context;
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
		m_ctorThreadId = getThreadId();
		WindowManager systemService = (WindowManager) m_context.getSystemService(Context.WINDOW_SERVICE);
		m_deviceRotation = systemService == null ? Surface.ROTATION_0 : systemService.getDefaultDisplay().getRotation();
	}

	@SuppressWarnings("unused")
	public void startListening() {
		throwIfCalledOnIncorrectThread();

		if (m_listeningForUpdates) {
			return;
		}

		m_listeningForUpdates = true;

		m_sensorManager = (SensorManager) m_context.getSystemService(Context.SENSOR_SERVICE);

		@SuppressWarnings("deprecation")
		Sensor orientation = m_sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
		m_sensorManager.registerListener(HeadingService.this, orientation, SensorManager.SENSOR_DELAY_GAME);

		m_orientationEventListener = new OrientationEventListener(m_context, SensorManager.SENSOR_DELAY_NORMAL) {
			@Override
			public void onOrientationChanged(int orientation) {
				m_deviceRotation = ((WindowManager) m_context.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay().getRotation();
			}
		};
		m_orientationEventListener.enable();
	}

	@SuppressWarnings("unused")
	public void stopListening() {
		throwIfCalledOnIncorrectThread();

		if (m_listeningForUpdates) {
			m_sensorManager.unregisterListener(HeadingService.this);
			m_orientationEventListener.disable();
		}
		m_listeningForUpdates = false;
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {

	}

	@SuppressWarnings("deprecation")
	@Override
	public void onSensorChanged(SensorEvent event) {
		if (event.sensor.getType() == Sensor.TYPE_ORIENTATION) {
			float smoothing = 0.6f;
			float heading = event.values[0];
			if (Float.isNaN(heading)) // Fix MPLY-4888
			{
				return;
			}
			float newAzimuth = adjustHeadingForDeviceOrientation(heading);

			if (Math.abs(newAzimuth - m_azimuthDegrees) >= 180) {
				if (newAzimuth > m_azimuthDegrees) {
					m_azimuthDegrees += 360.0f;
				} else {
					newAzimuth += 360.0f;
				}
			}
			m_azimuthDegrees = (float) ((newAzimuth * smoothing) + (m_azimuthDegrees * (1.0 - smoothing)));
			m_azimuthDegrees %= 360.0f;
		}

		updateNativeHeading(heading());
	}

	private float adjustHeadingForDeviceOrientation(float heading) {
		switch (m_deviceRotation) {
			case Surface.ROTATION_0:
				heading += 0.f;
				break;
			case Surface.ROTATION_90:
				heading += 90.f;
				break;
			case Surface.ROTATION_180:
				heading += 180.f;
				break;
			default:
				heading += 270.f;
				break;
		}

		heading = (heading + 360.f) % 360.f;
		return heading;
	}

	private void updateNativeHeading(final double heading) {
		m_nativeMessageRunner.runOnNativeThread(new Runnable() {
			public void run() {
				HeadingServiceJniMethods.UpdateHeading(m_nativeCallerPointer, heading);
			}
		});
	}
}
