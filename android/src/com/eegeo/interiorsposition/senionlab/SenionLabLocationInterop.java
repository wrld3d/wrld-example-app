package com.eegeo.interiorsposition.senionlab;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.senionlab.slutilities.service.SLConsumer;
import com.senionlab.slutilities.service.SLServiceManager;
import com.senionlab.slutilities.type.SLIndoorLocationException;

@SuppressWarnings("unused")
public class SenionLabLocationInterop implements SLConsumer
{
    private final MainActivity m_activity;
    private final SenionLabBroadcastReceiver m_broadcastReceiver;
    private final SLServiceManager m_serviceManager;
    private boolean m_consumerIsBound = false;
    
    private static AlertDialog m_connectionDialog = null;

    @SuppressWarnings("unused")
    public SenionLabLocationInterop(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_serviceManager = SLServiceManager.getInstance(m_activity);
        m_broadcastReceiver = new SenionLabBroadcastReceiver(m_activity, nativeCallerPointer);
    }

    private void askUserToEnableBluetoothIfDisabled()
    {
    	BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		if(bluetoothAdapter != null && !bluetoothAdapter.isEnabled())
		{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			m_activity.startActivity(enableBtIntent);
		}
    }
    
	@SuppressWarnings("unused")
    public void startUpdatingLocation(final String apiKey, final String apiSecret) {
        Log.v("SenionLabLocation", "startUpdatingLocation");
        askUserToEnableBluetoothIfDisabled();
        m_serviceManager.start(apiKey, apiSecret);
        bindService();
        m_serviceManager.registerReceiver(m_broadcastReceiver);
	}

    @SuppressWarnings("unused")
    public void stopUpdatingLocation()
    {
        Log.v("SenionLabLocation", "stopUpdatingLocation");
        unbindService();
        m_serviceManager.unregisterReceiver(m_broadcastReceiver);

        try {
            m_serviceManager.stop();
        } catch (SLIndoorLocationException slIndoorLocationException) {
            slIndoorLocationException.printStackTrace();
        }

        if (m_connectionDialog != null) {
            m_connectionDialog.dismiss();
            m_connectionDialog = null;
        }
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
    
    private void bindService()
    {
        Log.v("SenionLabLocation", "bindService");
        if (m_consumerIsBound) // || m_serviceManager.isBound(this)
        {
            return;
        }

        try
        {
            m_serviceManager.bindService(this);
        }
        catch(SLIndoorLocationException slIndoorLocationException)
        {
            slIndoorLocationException.printStackTrace();
        }

        m_consumerIsBound = true;
    }

    private void unbindService()
    {
        Log.v("SenionLabLocation", "unbindService");
        if (!m_consumerIsBound)
        {
            return;
        }

        try
        {
            m_serviceManager.unbindService(this);
        }
        catch(SLIndoorLocationException slIndoorLocationException)
        {
            slIndoorLocationException.printStackTrace();
        }

        m_consumerIsBound = false;
    }
}
