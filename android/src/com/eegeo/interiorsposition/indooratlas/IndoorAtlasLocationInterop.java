package com.eegeo.interiorsposition.indooratlas;

import android.app.AlertDialog;
import android.os.Bundle;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.indooratlas.android.sdk.IALocation;
import com.indooratlas.android.sdk.IALocationListener;
import com.indooratlas.android.sdk.IALocationManager;
import com.indooratlas.android.sdk.IALocationRequest;
import com.indooratlas.android.sdk.IARegion;

@SuppressWarnings("unused")
public class IndoorAtlasLocationInterop implements IALocationListener, IARegion.Listener
{
    private final MainActivity m_activity;
    private long m_nativeCallerPointer;
    
    private IALocationManager m_locationManager;
    private String m_floorPlanId;
    
    private static AlertDialog m_connectionDialog = null;

	@SuppressWarnings("unused")
    public IndoorAtlasLocationInterop(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

	@SuppressWarnings("unused")
	public void startUpdatingLocation(final String apiKey, final String apiSecret)
    {
		m_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				Bundle extras = new Bundle();
				extras.putString(IALocationManager.EXTRA_API_KEY, apiKey);
				extras.putString(IALocationManager.EXTRA_API_SECRET, apiSecret);
				m_locationManager = IALocationManager.create(m_activity, extras);
				m_locationManager.registerRegionListener(IndoorAtlasLocationInterop.this);
				
				IALocationRequest locationRequest = IALocationRequest.create();
				m_locationManager.requestLocationUpdates(locationRequest, IndoorAtlasLocationInterop.this);

                updateNativeIsAuthorized(true);
			}
		});
	}

	@SuppressWarnings("unused")
    public void stopUpdatingLocation()
    {
    	m_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				updateNativeIsAuthorized(false);
				
				if(m_locationManager != null)
				{
					m_locationManager.unregisterRegionListener(IndoorAtlasLocationInterop.this);
					m_locationManager.removeLocationUpdates(IndoorAtlasLocationInterop.this);
					m_locationManager = null;
				}
			}
		});
    	
    	if(m_connectionDialog != null)
		{
    		m_connectionDialog.dismiss();
    		m_connectionDialog = null;
		}
    }
    
    @Override
    public void onLocationChanged(IALocation location)
    {
    	updateNativeIsAuthorized(true);

    	updateNativeLocation(
    	        location.getLatitude(),
                location.getLongitude(),
				location.getAccuracy(),
				m_floorPlanId);
    }
    
    @Override
    public void onStatusChanged(String provider, int status, Bundle extras)
    {

    }
    
    @Override
    public void onEnterRegion(IARegion region)
    {
		if(region.getType() == IARegion.TYPE_FLOOR_PLAN)
		{
            m_floorPlanId = region.getId();
        }
    }
    
    @Override
    public void onExitRegion(IARegion region)
    {
    }

   	private void updateNativeLocation(
			final double latitudeDegrees,
			final double longitudeDegrees,
			final double horizontalAccuracyInMeters,
			final String floorId) {

		m_activity.runOnNativeThread(new Runnable() {
			public void run() {
				IndoorAtlasLocationInteropJniMethods.UpdateLocation(
						m_nativeCallerPointer,
						latitudeDegrees,
						longitudeDegrees,
						horizontalAccuracyInMeters,
						floorId);
			}
		});
	}

	private void updateNativeIsAuthorized(
			final boolean isAuthorized) {

		m_activity.runOnNativeThread(new Runnable() {
			public void run() {
				IndoorAtlasLocationInteropJniMethods.UpdateIsAuthorized(
						m_nativeCallerPointer,
						isAuthorized);
			}
		});
	}
}
