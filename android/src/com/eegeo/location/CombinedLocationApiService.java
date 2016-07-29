package com.eegeo.location;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.content.ContextCompat;
import android.util.Log;

public class CombinedLocationApiService
        implements GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener, LocationListener
{

    private Activity m_activity;
    protected static final String TAG = "CombinedLocationApiService";

    public static final long UPDATE_INTERVAL_IN_MILLISECONDS = 1000 * 60;
    public static final long FASTEST_UPDATE_INTERVAL_IN_MILLISECONDS = UPDATE_INTERVAL_IN_MILLISECONDS / 2;
    
    protected GoogleApiClient m_googleApiClient;
    protected LocationRequest m_locationRequest;
    protected Location m_currentLocation;
    private FusedLocationUpdateListener m_fusedLocationUpdateListener;

    public CombinedLocationApiService(Activity activity, FusedLocationUpdateListener fusedLocationUpdateListener)
    {
        this.m_activity = activity;
        this.m_fusedLocationUpdateListener = fusedLocationUpdateListener;
        startListeningToUpdates();
    }

    public void startListeningToUpdates()
    {
        buildGoogleApiClient();
    }

    private synchronized void buildGoogleApiClient()
    {
        if(ContextCompat.checkSelfPermission(m_activity,
                Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED)
        {
            return;
        }
        if(m_googleApiClient == null)
        {
            m_googleApiClient = new GoogleApiClient.Builder(m_activity).addConnectionCallbacks(this)
                    .addOnConnectionFailedListener(this).addApi(LocationServices.API).build();
        }
        createLocationRequest();
    }

    private void createLocationRequest()
    {
        if(m_locationRequest == null)
        {
            m_locationRequest = new LocationRequest();
            m_locationRequest.setInterval(UPDATE_INTERVAL_IN_MILLISECONDS);
            m_locationRequest.setFastestInterval(FASTEST_UPDATE_INTERVAL_IN_MILLISECONDS);
            m_locationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        }
        if(!m_googleApiClient.isConnected() && !m_googleApiClient.isConnecting())
            m_googleApiClient.connect();
    }

    private void startLocationUpdates()
    {
        LocationServices.FusedLocationApi.requestLocationUpdates(m_googleApiClient, m_locationRequest, this);
    }

    protected void stopLocationUpdates()
    {
        if(m_googleApiClient != null && m_googleApiClient.isConnected())
        {
            LocationServices.FusedLocationApi.removeLocationUpdates(m_googleApiClient, this);
            m_googleApiClient.disconnect();
            m_googleApiClient = null;
            m_locationRequest = null;
            m_currentLocation = null;
        }
    }

    @Override
    public void onConnected(Bundle connectionHint)
    {
        Log.v(TAG, "Connected to GoogleApiClient");
        if(m_currentLocation == null)
        {
            m_currentLocation = LocationServices.FusedLocationApi.getLastLocation(m_googleApiClient);
            if(this.m_fusedLocationUpdateListener != null && m_currentLocation != null)
            {
                this.m_fusedLocationUpdateListener.onFusedLocationChanged(m_currentLocation);
            }
        }
        startLocationUpdates();
    }

    @Override
    public void onLocationChanged(Location location)
    {
        Log.v(TAG, "onLocationChanged , " + location.getLatitude() + " : " + location.getLongitude());
        m_currentLocation = location;
        if(this.m_fusedLocationUpdateListener != null)
        {
            this.m_fusedLocationUpdateListener.onFusedLocationChanged(m_currentLocation);
        }
    }

    @Override
    public void onConnectionSuspended(int cause)
    {
        Log.v(TAG, "Connection suspended");
        m_googleApiClient.connect();
    }

    @Override
    public void onConnectionFailed(ConnectionResult result)
    {
        Log.v(TAG, "Connection failed: ConnectionResult.getErrorCode() = " + result.getErrorCode());
    }

    public interface FusedLocationUpdateListener
    {
        public void onFusedLocationChanged(Location location);
    }
}
