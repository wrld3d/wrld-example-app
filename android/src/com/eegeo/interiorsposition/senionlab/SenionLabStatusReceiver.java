package com.eegeo.interiorsposition.senionlab;

import android.support.annotation.NonNull;

import com.senion.ips.SenionIPS;
import com.senion.ips.SenionIPSError;

class SenionLabStatusReceiver extends SenionIPS.StatusListener
{
    private SenionLabBroadcastReceiver m_broadcastReceiver;

    public SenionLabStatusReceiver(SenionLabBroadcastReceiver broadcastReceiver)
    {
        m_broadcastReceiver = broadcastReceiver;
    }

    @Override
    public void onError(@NonNull SenionIPSError error)
    {
        m_broadcastReceiver.didLocationError(true);
    }
}
