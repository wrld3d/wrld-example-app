package com.eegeo.interiorsposition.senionlab;

import android.support.annotation.NonNull;

import com.senion.stepinside.sdk.PositioningApi;
import com.senion.stepinside.sdk.Subscription;
import com.senion.stepinside.sdk.Heading;
import com.senion.stepinside.sdk.Location;
import com.senion.stepinside.sdk.LocationAvailability;
import com.senion.stepinside.sdk.LocationSource;
import com.senion.stepinside.sdk.SenionLocationSource;

class SenionLabPositioningReceiver extends PositioningApi.Listener
{
    private final Object m_errorLock = new Object();
    private final Object m_updateLock = new Object();
    private long m_nativeCallerPointer;
    private SenionLabBroadcastReceiver m_broadcastReceiver;

    public SenionLabPositioningReceiver(SenionLabBroadcastReceiver broadcastReceiver, long nativeCallerPointer)
    {
        m_nativeCallerPointer = nativeCallerPointer;
        m_broadcastReceiver = broadcastReceiver;
    }

    @Override
    public void onLocationUpdated(@NonNull Location location)
    {
        synchronized (m_updateLock)
        {
            //TODO MOD make the destination for this accept a string and feed it location.getFloorId.getValue()
            SenionLabBroadcastReceiverJniMethods.DidUpdateLocation(m_nativeCallerPointer,
                                                                   location.getLatitude(),
                                                                   location.getLongitude(),
                                                                   0);//location.getFloorId().getValue());
        }
    }

    @Override
    public void onLocationSourceUpdated(@NonNull LocationSource locationSource)
    {
        if(locationSource instanceof SenionLocationSource)
        {
            SenionLocationSource senionLocationSource = ((SenionLocationSource) locationSource);
            SenionLabBroadcastReceiverJniMethods.SetInteriorIdFromMapKey(m_nativeCallerPointer, senionLocationSource.getMapKey().getValue());
        }
    }


    @Override
    public void onLocationAvailabilityUpdated(@NonNull LocationAvailability locationAvailability)
    {
    	boolean available = locationAvailability == LocationAvailability.Available;
    	SenionLabBroadcastReceiverJniMethods.SetIsConnected(m_nativeCallerPointer, available);
    }

    @Override
    public void onHeadingUpdated(@NonNull Heading heading)
    {
        m_broadcastReceiver.didLocationError(false);
    }
}
