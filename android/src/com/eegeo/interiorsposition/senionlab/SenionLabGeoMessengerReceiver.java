package com.eegeo.interiorsposition.senionlab;

import android.support.annotation.NonNull;

import com.senion.stepinside.sdk.GeoMessengerApi;
import com.senion.stepinside.sdk.Subscription;
import com.senion.stepinside.sdk.GeoMessengerZone;

class SenionLabGeoMessengerReceiver extends GeoMessengerApi.Listener
{
    private SenionLabBroadcastReceiver m_broadcastReceiver;

    public SenionLabGeoMessengerReceiver(SenionLabBroadcastReceiver broadcastReceiver)
    {
        m_broadcastReceiver = broadcastReceiver;
    }

    @Override
    public void onZoneEntered(@NonNull GeoMessengerZone zone) { m_broadcastReceiver.didLocationError(false); }

    @Override
    public void onZoneExited(@NonNull GeoMessengerZone zone) { m_broadcastReceiver.didLocationError(false); }
}
