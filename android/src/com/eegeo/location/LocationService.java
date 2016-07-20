// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.location;

import java.util.List;

import com.eegeo.location.CombinedLocationApiService.FusedLocationUpdateListener;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;

import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.util.Log;

class LocationService
{
    static boolean isListening = false;
    static boolean lastQuerySucceeded = false;
    static boolean locationValid = false;
    static Location bestLocation = null;
    static boolean isAuthorized = false;

    static CombinedLocationApiService m_combinedLocationApiService;
    
    public static double lat()
    {
        if (bestLocation == null)
        {
            return 0.0;
        }
        return bestLocation.getLatitude();
    }

    public static double lon()
    {
        if (bestLocation == null)
        {
            return 0.0;
        }
        return bestLocation.getLongitude();
    }

    public static double alt()
    {
        if(bestLocation == null)
        {
            return 0.0;
        }
        return bestLocation.getAltitude();
    }

    public static boolean hasAlt()
    {
        if(bestLocation == null)
        {
            return false;
        }
        return bestLocation.hasAltitude();
    }

    public static double accuracy()
    {
        if(bestLocation == null)
        {
            return 0.0;
        }
        return bestLocation.getAccuracy();
    }

    public static boolean hasAccuracy()
    {
        if(bestLocation == null)
        {
            return false;
        }
        return bestLocation.hasAccuracy();
    }
    
    public static boolean getIsAuthorized()
    {
    	return isAuthorized;
    }

    static LocationListener locationListener;
    static LocationManager locationManager;

    private static final int ONE_MINUTE = 1000 * 60;

    private static String exception;
    public static String exceptionMessage()
    {
        return exception;
    }

    public static boolean lastQuerySucceeded()
    {
        return bestLocation != null;
    }

    public static boolean locationValid()
    {
        return bestLocation != null;
    }

    public static void startListeningToUpdates(Activity a)
    {
        if (!isListening)
        {
            setupListenerAndLocationManager(a);
            forceLocationFromCachedProviders(LocationService.locationManager);

            try
            {
                if (LocationService.locationListener != null)
                {
                    LocationService.locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, LocationService.locationListener);
                    LocationService.locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, LocationService.locationListener);
                }
            }
            catch (Exception e)
            {
                Log.v("Location", e.getMessage());
            }
        }
    }

    public static void stopListeningToUpdates(Activity a)
    {
        if(m_combinedLocationApiService != null)
        {
            m_combinedLocationApiService.stopLocationUpdates();
            isListening = false;
        }
        else if(isListening)
        {
            LocationService.locationManager.removeUpdates(LocationService.locationListener);
            tearDownListener();
        }
    }

    public static void updateLocation(Activity a)
    {
        if(GooglePlayServicesUtil.isGooglePlayServicesAvailable(a) == ConnectionResult.SUCCESS)
        {
            LocationService.locationManager = (LocationManager) a.getSystemService(Context.LOCATION_SERVICE);
            LocationService.isListening = LocationService.isAuthorized = isAnyProviderEnabled(LocationService.locationManager);

            if(m_combinedLocationApiService == null)
            {
                m_combinedLocationApiService = new CombinedLocationApiService(a, new FusedLocationUpdateListener()
                {
                    @Override
                    public void onFusedLocationChanged(Location location)
                    {
                        LocationService.bestLocation = location;
                    }
                });
            }
            else
            {
                m_combinedLocationApiService.startListeningToUpdates();
            }
            if(LocationService.bestLocation == null)
            {
                forceLocationFromCachedProviders(LocationService.locationManager);
            }
        }
        else
        {
            LocationService.startListeningToUpdates(a);
        }
    }

    private static void forceLocationFromCachedProviders(LocationManager locationManager)
    {
        List<String> providers = locationManager.getProviders(true);
        Location bestCachedLocation = null;
        for (String provider : providers)
        {
            Location l = locationManager.getLastKnownLocation(provider);
            if (l == null)
            {
                continue;
            }
            if (isBetterLocation(l, bestCachedLocation))
            {
                bestCachedLocation = l;
            }
        }

        LocationService.bestLocation = bestCachedLocation;
        Log.v("Location", "best location set from cache");
    }

    private static void tearDownListener()
    {
        if (LocationService.locationManager != null)
        {
            LocationService.locationManager = null;
        }
        if (LocationService.locationListener != null)
        {
            LocationService.locationListener = null;
            isListening = false;
        }
    }

    private static boolean isAnyProviderEnabled(LocationManager locationManager)
    {
    	if(locationManager == null)
    	{
    		return false;
    	}
    	
    	boolean gpsIsAuthorized = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
    	boolean networkIsAuthorized = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
    	return (gpsIsAuthorized || networkIsAuthorized);
    }
    
    private static void setupListenerAndLocationManager(Activity a)
    {
        LocationService.locationManager = (LocationManager) a.getSystemService(Context.LOCATION_SERVICE);

        LocationService.isAuthorized = isAnyProviderEnabled(LocationService.locationManager);
        
        if (LocationService.locationListener == null)
        {
            LocationService.locationListener = new LocationListener()
            {

                public void onLocationChanged(Location location)
                {
                    if (isBetterLocation(location, LocationService.bestLocation))
                    {
                        LocationService.bestLocation = location;
                        Log.v("Location", "best updated from onLocationChanged : " + location.getLatitude() + " , " + location.getLongitude());
                    }
                }

                public void onStatusChanged(String provider, int status, Bundle extras)
                {
                    Log.v("Location", "onStatusChanged");
                }

                public void onProviderEnabled(String provider)
				{
					LocationService.isAuthorized = isAnyProviderEnabled(LocationService.locationManager);
					Log.v("Location", "onProviderEnabled, LocationService.isAuthorized : " + LocationService.isAuthorized);
				}
				
				public void onProviderDisabled(String provider)
				{
					LocationService.isAuthorized = isAnyProviderEnabled(LocationService.locationManager);
					Log.v("Location", "onProviderDisabled, LocationService.isAuthorized : " + LocationService.isAuthorized);
				}        	   
            };
        }
        isListening = true;
    }

    // Hoick http://developer.android.com/guide/topics/location/strategies.html
    protected static boolean isBetterLocation(Location location, Location currentBestLocation)
    {
        if (currentBestLocation == null)
        {
            // A new location is always better than no location
            return true;
        }

        // Check whether the new location fix is newer or older
        long timeDelta = location.getTime() - currentBestLocation.getTime();
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
}