package com.eegeo.indooratlas;

import java.util.Locale;

import android.os.Bundle;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.indooratlas.android.sdk.IALocation;
import com.indooratlas.android.sdk.IALocationListener;
import com.indooratlas.android.sdk.IALocationManager;
import com.indooratlas.android.sdk.IALocationRequest;
import com.indooratlas.android.sdk.IARegion;

public class IndoorAtlasManager implements IALocationListener, IARegion.Listener  
{
	private final String TAG = "IndoorAtlasManager";
	private MainActivity m_activity;
	private long m_nativeCallerPointer;
	
	private IALocationManager m_locationManager;
	
	
	public IndoorAtlasManager(MainActivity activity,
							  long nativeCallerPointer)
	{
		Log.d(TAG, "IndoorAtlasManager()");
		
		m_activity = activity; 
		m_nativeCallerPointer = nativeCallerPointer;
	}

	public void StartUpdatingLocation(final String apiKey,
									  final String apiSecret,
									  final String planId)
	{
		Log.d(TAG, "StartUpdatingLocationWithFloorPlanId:" + planId);
		m_activity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run() 
			{
				if(m_locationManager == null)
				{
					final Bundle extras = new Bundle(2);
					extras.putString(IALocationManager.EXTRA_API_KEY, apiKey);
			        extras.putString(IALocationManager.EXTRA_API_SECRET, apiSecret);
					m_locationManager = IALocationManager.create(m_activity, extras);
				}
				
				IALocationRequest request = IALocationRequest.create();
				request.setFastestInterval(100);
  				m_locationManager.registerRegionListener(IndoorAtlasManager.this);
				m_locationManager.removeLocationUpdates(IndoorAtlasManager.this);
				m_locationManager.requestLocationUpdates(request, IndoorAtlasManager.this);
				
				final IARegion region = IARegion.floorPlan(planId);
				m_locationManager.setLocation(IALocation.from(region));
			}
		});
	}
	
	public void SetFloorIndex(final String planId) 
	{
		m_activity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run() 
			{
				if(m_locationManager!=null) 
				{
					Log.d(TAG, "SetFloorIndex: " + planId);
					IALocationRequest request = IALocationRequest.create();
					request.setFastestInterval(100);
					m_locationManager.registerRegionListener(IndoorAtlasManager.this);
					m_locationManager.removeLocationUpdates(IndoorAtlasManager.this);
					m_locationManager.requestLocationUpdates(request, IndoorAtlasManager.this);
					
					final IARegion region = IARegion.floorPlan(planId);
					m_locationManager.setLocation(IALocation.from(region));
				}
			}
		});
	}
	
	public void StopUpdatingLocation()
	{
		m_activity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run() 
			{
				if(m_locationManager!=null) 
				{
					m_locationManager.unregisterRegionListener(IndoorAtlasManager.this);
					m_locationManager.removeLocationUpdates(IndoorAtlasManager.this);
					m_locationManager.destroy();
					m_locationManager = null;
				}
			}
		});
	}
	
	@Override
	public void onLocationChanged(IALocation location) 
	{
		Log.d(TAG, String.format(Locale.US, "%f,%f, accuracy: %.2f", location.getLatitude(), location.getLongitude(), location.getAccuracy()));
		IndoorAtlasJniMethods.OnLocationChanged(m_nativeCallerPointer, location.getLatitude(), location.getLongitude());
	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) 
	{
		switch (status) {
        case IALocationManager.STATUS_CALIBRATION_CHANGED:
            String quality = "unknown";
            switch (extras.getInt("quality")) 
            {
                case IALocationManager.CALIBRATION_POOR:
                    quality = "Poor";
                    break;
                case IALocationManager.CALIBRATION_GOOD:
                    quality = "Good";
                    break;
                case IALocationManager.CALIBRATION_EXCELLENT:
                    quality = "Excellent";
                    break;
            }
            Log.d(TAG, "Calibration change. Quality: " + quality);
            break;
        case IALocationManager.STATUS_AVAILABLE:
        	Log.d(TAG, "onStatusChanged: Available");
            break;
        case IALocationManager.STATUS_LIMITED:
        	Log.d(TAG, "onStatusChanged: Limited");
            break;
        case IALocationManager.STATUS_OUT_OF_SERVICE:
        	Log.d(TAG, "onStatusChanged: Out of service");
            break;
        case IALocationManager.STATUS_TEMPORARILY_UNAVAILABLE:
        	Log.d(TAG, "onStatusChanged: Temporarily unavailable");
		}
	}

	@Override
	public void onEnterRegion(IARegion region) 
	{
		Log.d(TAG, "onEnterRegion: " + region.getType() + ", " + region.getId());
	}

	@Override
	public void onExitRegion(IARegion region) 
	{
		Log.d(TAG, "onEnterRegion: " + region.getType() + ", " + region.getId());
	}
	
	public void destroy()
    {
		Log.d(TAG, "destroy()");
		m_locationManager = null;
    }
}
