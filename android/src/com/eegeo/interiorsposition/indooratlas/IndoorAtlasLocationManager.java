package com.eegeo.interiorsposition.indooratlas;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.indooratlas.android.sdk.IALocation;
import com.indooratlas.android.sdk.IALocationListener;
import com.indooratlas.android.sdk.IALocationManager;
import com.indooratlas.android.sdk.IALocationRequest;
import com.indooratlas.android.sdk.IARegion;

public class IndoorAtlasLocationManager implements IALocationListener, IARegion.Listener
{
    private final MainActivity m_activity;
    private long m_nativeCallerPointer;
    
    private IALocationManager m_locationManager;
    private String m_floorPlanId;
    
    private static AlertDialog m_connectionDialog = null;

    public IndoorAtlasLocationManager(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

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
				m_locationManager.registerRegionListener(IndoorAtlasLocationManager.this);
				
				IALocationRequest locationRequest = IALocationRequest.create();
				m_locationManager.requestLocationUpdates(locationRequest, IndoorAtlasLocationManager.this);
				
				IndoorAtlasLocationManagerJniMethods.SetIsAuthorized(m_nativeCallerPointer, true);
			}
		});
	}

    public void stopUpdatingLocation()
    {
    	m_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				IndoorAtlasLocationManagerJniMethods.SetIsAuthorized(m_nativeCallerPointer, false);
				
				if(m_locationManager != null)
				{
					m_locationManager.unregisterRegionListener(IndoorAtlasLocationManager.this);
					m_locationManager.removeLocationUpdates(IndoorAtlasLocationManager.this);
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
    	IndoorAtlasLocationManagerJniMethods.SetIsAuthorized(m_nativeCallerPointer, true);
    	IndoorAtlasLocationManagerJniMethods.DidUpdateLocation(m_nativeCallerPointer, location.getLatitude(), location.getLongitude(), m_floorPlanId);
    }
    
    @Override
    public void onStatusChanged(String provider, int status, Bundle extras)
    {
    	switch(status)
    	{
        case IALocationManager.STATUS_AVAILABLE:
            showConnectionDialog("IndoorAtlas available", "Recently connected to IndoorAtlas.");
            break;
        case IALocationManager.STATUS_TEMPORARILY_UNAVAILABLE:
            showConnectionDialog("IndoorAtlas unavailable", "Recently lost connection to IndoorAtlas.");
            break;
    	}
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
    
    private void showConnectionDialog(String Title, String message)
    {
    	/*
    	AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle(Title);
        builder.setMessage(message);
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
            	m_connectionDialog.dismiss();
            	m_connectionDialog = null;
            }
        });
        
        if(m_connectionDialog != null)
        {
        	m_connectionDialog.dismiss();
        }
        m_connectionDialog = builder.show();
        //*/
    }
}
