package com.eegeo.interiorsposition.senionlab;

import android.content.Context;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.senionlab.slutilities.service.SLBroadcastReceiver;
import com.senionlab.slutilities.service.SLConsumer;
import com.senionlab.slutilities.service.SLServiceManager;
import com.senionlab.slutilities.type.SLIndoorLocationException;

public class SenionLabLocationManager implements SLConsumer
{
    private final MainActivity m_activity;
    private final SLServiceManager m_serviceManager;
    private boolean m_consumerIsBound = false;

    public SenionLabLocationManager(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_serviceManager = SLServiceManager.getInstance(m_activity);
    }

	public void startUpdatingLocation(final String apiKey, final String apiSecret) throws SLIndoorLocationException
    {
        m_serviceManager.start(apiKey, apiSecret);
        bindService();
	}

    public void stopUpdatingLocation() throws SLIndoorLocationException
    {
        unbindService();
        m_serviceManager.stop();
    }

    public void registerReceiver(SLBroadcastReceiver receiver)
    {
        m_serviceManager.registerReceiver(receiver);
    }

    public void unregisterReceiver(SLBroadcastReceiver receiver)
    {
        m_serviceManager.unregisterReceiver(receiver);
    }

    @Override
    public Context getContext()
    {
        return m_activity.getApplicationContext();
    }

    @Override
    public void didBindToService()
    {
    }

    private void bindService() throws SLIndoorLocationException
    {
        if (!m_consumerIsBound)
        {
            m_serviceManager.bindService(this);
            m_consumerIsBound = true;
        }
    }

    private void unbindService() throws SLIndoorLocationException
    {
        if (m_consumerIsBound)
        {
            m_serviceManager.unbindService(this);
            m_consumerIsBound = false;
        }
    }
}
