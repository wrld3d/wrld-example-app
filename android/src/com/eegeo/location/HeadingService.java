// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.location;

import java.util.ArrayDeque;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Surface;
import android.view.WindowManager;

public class HeadingService implements SensorEventListener
{
    private SensorManager m_sensorManager;
    private Activity m_activity;
    private boolean m_hasAzimuthAngle = false;
    private boolean m_listeningForUpdates = false;

    // The results from SensorManager.getOrientation appear to be worse than the results of
    // the deprecated Sensor.TYPE_ORIENTATION on the test device. To enable SensorManager.getOrientation
    // using the results of the Sensor.TYPE_GRAVITY and Sensor.TYPE_MAGNETIC_FIELD sensors, set
    // this field to false. The results of this have high jitter, so a low-pass filter is used. Even
    // then, the results appear to be inferior to Sensor.TYPE_ORIENTATION.
    private final boolean m_useDeprecatedOrientationMethod = false;

    // Used if m_useDeprecatedOrientationMethod == true.
    private float m_azimuthDegrees = 0.f;

    // Used if m_useDeprecatedOrientationMethod == false.
    private float[] m_gravity = new float[3];
    private float[] m_geomagnetic = new float[3];

    public boolean hasHeading()
    {
        return m_hasAzimuthAngle;
    }

    public double heading()
    {
        return m_azimuthDegrees;
    }

    public HeadingService(Activity activity)
    {
        m_activity = activity;
    }

    public void startListening()
    {
        if (m_listeningForUpdates)
        {
            return;
        }

        m_listeningForUpdates = true;

        m_sensorManager = (SensorManager)m_activity.getSystemService(Context.SENSOR_SERVICE);

        if(m_useDeprecatedOrientationMethod)
        {
            @SuppressWarnings("deprecation")
            Sensor orientation = m_sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
            m_sensorManager.registerListener(this, orientation, SensorManager.SENSOR_DELAY_GAME);
        }
        else
        {
            Sensor accelerometer = m_sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            Sensor magnetometer = m_sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
            m_sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_GAME);
            m_sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_GAME);
        }
    }

    public void stopListening()
    {
        if(m_listeningForUpdates)
        {
            m_sensorManager.unregisterListener(this);
        }
        m_listeningForUpdates = false;
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy)
    {

    }

    @SuppressWarnings("deprecation")
    @Override
    public void onSensorChanged(SensorEvent event)
    {
        if(m_useDeprecatedOrientationMethod)
        {
            if (event.sensor.getType() == Sensor.TYPE_ORIENTATION)
            {
                float smoothing = 0.6f;
                float heading = event.values[0];
                float pitch = event.values[1];
                float roll = event.values[2];
                if (Float.isNaN(heading) || (heading == 0 && (Float.isNaN(pitch) || pitch == 0) && (Float.isNaN(roll) || roll == 0))) // Fix MPLY-4888 || Fix MPLY-7637
                {
                    return;
                }
                float newAzimuth = adjustHeadingForDeviceOrientation(heading);
                
                if(Math.abs(newAzimuth - m_azimuthDegrees) >= 180)
                {
                    if(newAzimuth > m_azimuthDegrees)
                    {
                        m_azimuthDegrees += 360.0f;
                    }
                    else
                    {
                        newAzimuth += 360.0f;
                    }
                }
                m_azimuthDegrees = (float) ((newAzimuth * smoothing) + (m_azimuthDegrees * (1.0 - smoothing)));     
                m_azimuthDegrees %= 360.0f;
                m_hasAzimuthAngle = true;
                return;
            }
        }
        else
        {
            if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
            {
                m_gravity = event.values.clone();
            }

            if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD)
            {
                m_geomagnetic = event.values.clone();
            }

            if (m_gravity != null && m_geomagnetic != null)
            {
                float R[] = new float[9];
                float I[] = new float[9];
                boolean success = SensorManager.getRotationMatrix(R, I, m_gravity, m_geomagnetic);
                if(success)
                {
                    float remap[] = new float[9];
                    adjustHeadingForDeviceOrientation(R, remap);
                    
                    float orientation[] = new float[3];
                    SensorManager.getOrientation(remap, orientation);

                    float newAzimuth = (float) Math.toDegrees(orientation[0]);
                    
                    if(Math.abs(newAzimuth - m_azimuthDegrees) >= 180)
                    {
                        if(newAzimuth > m_azimuthDegrees)
                        {
                            m_azimuthDegrees += 360.0f;
                        }
                        else
                        {
                            newAzimuth += 360.0f;
                        }
                    }
                    
                    float threshold = 25f;
                    float diff = m_azimuthDegrees - newAzimuth;
                    diff /= threshold;
                    diff = Math.min(diff, diff * diff);
                    m_azimuthDegrees -= diff;
                    m_azimuthDegrees = (m_azimuthDegrees + 360f) % 360;
                    m_hasAzimuthAngle = true;
                }
            }
        }
    }

    private float adjustHeadingForDeviceOrientation(float heading)
    {
        final int rotation = ((WindowManager) this.m_activity.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay().getRotation();

        switch (rotation)
        {
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

        heading = (heading + 360.f)%360.f;
        return heading;
    }
    
    private void adjustHeadingForDeviceOrientation(float rotationMatrix[], float remap[])
    {
    	final int rotation = ((WindowManager) this.m_activity.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay().getRotation();

        switch (rotation)
        {
        case Surface.ROTATION_0:
        	SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_X, SensorManager.AXIS_Y, remap);
            break;
        case Surface.ROTATION_90:
        	SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_Y, SensorManager.AXIS_MINUS_X, remap);
            break;
        case Surface.ROTATION_180:
        	SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_MINUS_X, SensorManager.AXIS_MINUS_Y, remap);
            break;
        default:
        	SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_MINUS_Y, SensorManager.AXIS_X, remap);
            break;
        }
    }
}
