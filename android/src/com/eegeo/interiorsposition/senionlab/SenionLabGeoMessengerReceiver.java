package com.eegeo.interiorsposition.senionlab;

import androidx.annotation.NonNull;

import com.senion.ips.ZoneDetectionApi;
import com.senion.ips.Zone;

class SenionLabGeoMessengerReceiver extends ZoneDetectionApi.Listener
{
    private SenionLabBroadcastReceiver m_broadcastReceiver;

    public SenionLabGeoMessengerReceiver(SenionLabBroadcastReceiver broadcastReceiver)
    {
        m_broadcastReceiver = broadcastReceiver;
    }

    @Override
    public void onZoneEntered(@NonNull Zone zone) { m_broadcastReceiver.didLocationError(false); }

    @Override
    public void onZoneExited(@NonNull Zone zone) { m_broadcastReceiver.didLocationError(false); }
}
