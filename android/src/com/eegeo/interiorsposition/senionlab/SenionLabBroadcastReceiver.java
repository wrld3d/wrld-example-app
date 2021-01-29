package com.eegeo.interiorsposition.senionlab;

//import com.senion.ips.Subscription;

class SenionLabBroadcastReceiver
{
    private long m_nativeCallerPointer;
    private SenionLabLocationManager m_locationManager;

    private final Object m_errorLock = new Object();

 //   private Subscription m_geoMessengerReceiver;
 //   private Subscription m_positioningReceiver;
 //   private Subscription m_statusReceiver;

    public SenionLabBroadcastReceiver(SenionLabLocationManager locationManager, long nativeCallerPointer)
    {
        m_nativeCallerPointer = nativeCallerPointer;
        m_locationManager = locationManager;
    }

    public void registerReceiver()
    {
        m_locationManager.onSdkReady(new SenionLabLocationManager.SdkReadyCallback()
        {
            @Override
            public void invoke()
            {
                sdkReady();
            }
        });
    }

    public void unregisterReceiver()
    {
     /*   if(m_geoMessengerReceiver != null)
        {
            m_locationManager.unregisterReceiver(m_geoMessengerReceiver);
        }
        if(m_positioningReceiver != null)
        {
            m_locationManager.unregisterReceiver(m_positioningReceiver);
        }
        if(m_statusReceiver != null)
        {
            m_locationManager.unregisterReceiver(m_statusReceiver);
        }*/
    }

    private void sdkReady()
    {
        /*m_geoMessengerReceiver = m_locationManager.registerGeoMessengerReceiver(new SenionLabGeoMessengerReceiver(this));
        m_positioningReceiver = m_locationManager.registerPositioningReceiver(new SenionLabPositioningReceiver(this, m_nativeCallerPointer));
        m_statusReceiver = m_locationManager.registerStatusReceiver(new SenionLabStatusReceiver(this));*/
    }

    public void didLocationError(final boolean didError)
    {
        synchronized (m_errorLock)
        {
            SenionLabBroadcastReceiverJniMethods.SetIsAuthorized(m_nativeCallerPointer, !didError);
        }
    }
}