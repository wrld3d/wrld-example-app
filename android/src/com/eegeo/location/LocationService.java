// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.location;

import java.util.List;

import com.eegeo.mapapi.INativeMessageRunner;
import com.eegeo.location.CombinedLocationApiService.FusedLocationUpdateListener;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.text.TextUtils;
import android.util.Log;

@SuppressWarnings("unused")
class LocationService {
    private final long m_nativeCallerPointer;
    private final INativeMessageRunner m_nativeMessageRunner;
    private Location m_bestLocation = null;
    private boolean m_isListening = false;
    private boolean m_isAuthorized = false;

    private CombinedLocationApiService m_combinedLocationApiService;

    private Context m_context;

    private LocationListener m_locationListener;
    private LocationManager m_locationManager;

    @SuppressWarnings("unused")
    public LocationService(
            Context context,
            INativeMessageRunner nativeMessageRunner,
            long nativeCallerPointer) {
        if(context == null) {
            throw new NullPointerException("context");
        }

        if(nativeMessageRunner == null) {
            throw new NullPointerException("nativeMessageRunner");
        }

        m_context = context;
        m_nativeMessageRunner = nativeMessageRunner;
        m_nativeCallerPointer = nativeCallerPointer;
        m_isAuthorized = isLocationEnabled(m_context);

        Log.v("Location", "ctor; is authorized? : " + m_isAuthorized);

        // this could be re-entrant. Might be better to expose isAuthorized method and just call it
        // from C++ the first time.
        updateNativeAuthorized(m_isAuthorized);
    }

    // TODO: not sure which of these checks is the best
    private static boolean isLocationEnabled(Context context) {
        String locationProviders;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            try {
                return Settings.Secure.getInt(context.getContentResolver(), Settings.Secure.LOCATION_MODE) !=
                        Settings.Secure.LOCATION_MODE_OFF;
            } catch (Settings.SettingNotFoundException e) {
                return false;
            }
        }

        locationProviders = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.LOCATION_PROVIDERS_ALLOWED);
        return !TextUtils.isEmpty(locationProviders);
    }

    private boolean hasUserGrantedLocationPermissions() {
        final boolean hasFineLocationPermission =
                ActivityCompat.checkSelfPermission(m_context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED;

        final boolean hasCoarseLocationPermission =
               ActivityCompat.checkSelfPermission(m_context, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED;

        Log.v("Location", "location: ACCESS_FINE_LOCATION permission = " + hasFineLocationPermission);
        Log.v("Location", "location: ACCESS_COARSE_LOCATION permission = " + hasCoarseLocationPermission);

        return hasFineLocationPermission && hasCoarseLocationPermission;
    }

    @SuppressWarnings({"unused", "WeakerAccess"})
    public void startListeningToUpdates() {
        try {
            if (m_isListening) {
                return;
            }

            setupListenerAndLocationManager();
            forceLocationFromCachedProviders();

            if (m_locationListener != null) {
                if (!hasUserGrantedLocationPermissions()) {
                    return;
                }

                Log.v("Location", "requesting location updates for GPS_PROVIDER & NETWORK_PROVIDER");
                m_locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, m_locationListener);
                m_locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, m_locationListener);
            }
        }
        catch (Exception e)
        {
            Log.v("Location", e.getMessage());
        }
    }

    @SuppressWarnings("unused")
    public void stopListeningToUpdates()
    {
        if (m_combinedLocationApiService != null) {
            m_combinedLocationApiService.stopLocationUpdates();
            m_isListening = false;
        } else if (m_isListening) {
            tearDownListener();
        }
    }

    private void forceLocationFromCachedProviders()
    {
        List<String> providers = m_locationManager.getProviders(true);
        Location bestCachedLocation = null;
        for (String provider : providers)
        {
            Location l = m_locationManager.getLastKnownLocation(provider);

            if (l == null)
            {
                continue;
            }

            if (isBetterLocation(l, bestCachedLocation))
            {
                bestCachedLocation = l;
            }
        }

        m_bestLocation = bestCachedLocation;

        if(m_bestLocation != null) {
            updateNativeLocation(
                    m_bestLocation.getLatitude(),
                    m_bestLocation.getLongitude(),
                    m_bestLocation.getAltitude(),
                    m_bestLocation.getAccuracy());
        }

        Log.v("Location", "best location set from cache");
    }

    private void tearDownListener()
    {
        if (m_locationManager != null)
        {
            m_locationManager.removeUpdates(m_locationListener);
            m_locationManager = null;
        }

        m_locationListener = null;
        m_isListening = false;
    }

    private boolean isAnyProviderEnabled()
    {
    	if(m_locationManager == null)
    	{
    		return false;
    	}
    	
    	boolean gpsIsAuthorized = m_locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
    	boolean networkIsAuthorized = m_locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
    	return (gpsIsAuthorized || networkIsAuthorized);
    }
    
    private void setupListenerAndLocationManager()
    {
        m_locationManager = (LocationManager) m_context.getSystemService(Context.LOCATION_SERVICE);
        m_isAuthorized = isAnyProviderEnabled();

        final int resultCode = GoogleApiAvailability
                .getInstance()
                .isGooglePlayServicesAvailable(m_context);

        if(resultCode == ConnectionResult.SUCCESS) {
            if(m_combinedLocationApiService == null) {
                CreateCombinedLocationService();
            }
            else {
                m_combinedLocationApiService.startListeningToUpdates();
            }

            if(m_bestLocation == null) {
                forceLocationFromCachedProviders();
            }
        }
        else
        {
           if (m_locationListener == null) {
               CreateFallbackLocationListener();
           }
        }
        m_isListening = true;
    }

    private void CreateCombinedLocationService() {
        Log.v("Location", "Creating CombinedLocationApiService");
        m_combinedLocationApiService = new CombinedLocationApiService(m_context, new FusedLocationUpdateListener()
        {
            @Override
            public void onFusedLocationChanged(Location location)
            {
                m_bestLocation = location;
                updateNativeLocation(
                        location.getLatitude(),
                        location.getLongitude(),
                        location.getAltitude(),
                        location.getAccuracy());
            }
        });
    }

    private void CreateFallbackLocationListener() {
        Log.v("Location", "Creating LocationListener as a fallback");
        m_locationListener = new LocationListener() {
            public void onLocationChanged(Location location) {
                if (isBetterLocation(location, m_bestLocation)) {
                    m_bestLocation = location;
                    updateNativeLocation(location.getLatitude(), location.getLongitude(), location.getAltitude(), location.getAccuracy());
                    Log.v("Location", "best updated from onLocationChanged : " + location.getLatitude() + " , " + location.getLongitude());
                }
            }

            public void onStatusChanged(String provider, int status, Bundle extras) {
                Log.v("Location", "onStatusChanged");
            }

            public void onProviderEnabled(String provider) {
                m_isAuthorized = isAnyProviderEnabled();
                updateNativeAuthorized(m_isAuthorized);
                Log.v("Location", "onProviderEnabled, LocationService.m_isAuthorized : " + m_isAuthorized);
            }

            public void onProviderDisabled(String provider) {
                m_isAuthorized = isAnyProviderEnabled();
                updateNativeAuthorized(m_isAuthorized);
                Log.v("Location", "onProviderDisabled, LocationService.m_isAuthorized : " + m_isAuthorized);
            }
        };
    }

    // Hoick http://developer.android.com/guide/topics/location/strategies.html
    private boolean isBetterLocation(Location location, Location currentBestLocation)
    {
        if (currentBestLocation == null)
        {
            // A new location is always better than no location
            return true;
        }

        // Check whether the new location fix is newer or older
        long timeDelta = location.getTime() - currentBestLocation.getTime();

        final int ONE_MINUTE = 1000 * 60;

        boolean isSignificantlyNewer = timeDelta > ONE_MINUTE;
        boolean isSignificantlyOlder = timeDelta < -ONE_MINUTE;
        boolean isNewer = timeDelta > 0;

        // If it's been more than two minutes since the current location, use the new location
        // because the user has likely moved
        if (isSignificantlyNewer)
        {
            return true;
            // If the new location is more than two minutes older, it must be worse
        }
        else if (isSignificantlyOlder)
        {
            return false;
        }

        // Check whether the new location fix is more or less accurate
        int accuracyDelta = (int) (location.getAccuracy() - currentBestLocation.getAccuracy());
        boolean isLessAccurate = accuracyDelta > 0;
        boolean isMoreAccurate = accuracyDelta < 0;
        boolean isSignificantlyLessAccurate = accuracyDelta > 200;

        // Check if the old and new location are from the same provider
        boolean isFromSameProvider = isSameProvider(location.getProvider(),
                                     currentBestLocation.getProvider());

        // Determine location quality using a combination of timeliness and accuracy
        if (isMoreAccurate)
        {
            return true;
        }
        else if (isNewer && !isLessAccurate)
        {
            return true;
        }
        else if (isNewer && !isSignificantlyLessAccurate && isFromSameProvider)
        {
            return true;
        }
        return false;
    }

    /** Checks whether two providers are the same */
    private static boolean isSameProvider(String provider1, String provider2)
    {
        if (provider1 == null)
        {
            return provider2 == null;
        }
        return provider1.equals(provider2);
    }

    private void updateNativeLocation(
            final double latitudeDegrees,
            final double longitudeDegrees,
            final double altitudeMeters,
            final double horizontalAccuracyMeters)
    {
        //m_nativeMessageRunner.runOnNativeThread(new Runnable()
        //{
        //    public void run() {
                LocationServiceJniMethods.UpdateLocation(
                        m_nativeCallerPointer,
                        latitudeDegrees,
                        longitudeDegrees,
                        altitudeMeters,
                        horizontalAccuracyMeters);
        //    }
        //});
    }

    private void updateNativeAuthorized(final boolean isAuthorized)
    {
        //m_nativeMessageRunner.runOnNativeThread(new Runnable() {
        //    public void run()
        //   {
                LocationServiceJniMethods.UpdateAuthorized(
                        m_nativeCallerPointer,
                        isAuthorized);
        //    }
        //});
    }
}