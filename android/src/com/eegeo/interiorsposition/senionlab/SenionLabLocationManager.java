package com.eegeo.interiorsposition.senionlab;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;

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
    
    private static AlertDialog m_connectionDialog = null;

    public SenionLabLocationManager(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_serviceManager = SLServiceManager.getInstance(m_activity);
    }

    public void askUserToEnableBluetoothIfDisabled()
    {
    	BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		if(bluetoothAdapter != null && !bluetoothAdapter.isEnabled())
		{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			m_activity.startActivity(enableBtIntent);
		}
    }
    
	public void startUpdatingLocation(final String apiKey, final String apiSecret) throws SLIndoorLocationException
    {
		m_serviceManager.start(apiKey, apiSecret);
		bindService();
	}

    public void stopUpdatingLocation()
    {
        unbindService();
        
        try
        {
        	m_serviceManager.stop();
        }
        catch(SLIndoorLocationException slIndoorLocationException)
    	{
    		slIndoorLocationException.printStackTrace();
    	}
        
        if(m_connectionDialog != null)
		{
    		m_connectionDialog.dismiss();
    		m_connectionDialog = null;
		}
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
    
    public void updateAvailability(boolean available)
    {
    	if(available)
    	{
    		showConnectionDialog("Senion available", "Recently connected to Senion.");
    	}
    	else
    	{
    		showConnectionDialog("Senion unavailable", "Recently lost connection to Senion.");
    	}
    }

    private void bindService()
    {
        if (!m_consumerIsBound)
        {
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
    }

    private void unbindService()
    {
        if (m_consumerIsBound)
        {
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
    
    private void showConnectionDialog(String Title, String message)
    {
    	/*
    	AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle(Title);
        builder.setMessage(message);
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
            	m_connectionDialog.dismiss();
            	m_connectionDialog = null;
            }
        });
        
        if(m_connectionDialog != null)
        {
        	m_connectionDialog.dismiss();
        }
        m_connectionDialog = builder.show();
        //*/
    }
}
