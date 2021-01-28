package com.eegeo.interiorsposition.senionlab;

import androidx.annotation.NonNull;

import com.senion.ips.PositioningApi;
import com.senion.ips.Heading;
import com.senion.ips.Location;

class SenionLabPositioningReceiver extends PositioningApi.Listener
{
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

            SenionLabBroadcastReceiverJniMethods.DidUpdateLocation(m_nativeCallerPointer,
                                                                   location.getLatitude(),
                                                                   location.getLongitude(),
                                                                   location.getUncertaintyRadius(),
                                                                    Integer.getInteger(location.getFloorId().getValue())
            );
        }
    }

    @Override
    public void onHeadingUpdated(@NonNull Heading heading)
    {
        m_broadcastReceiver.didLocationError(false);
    }
}
