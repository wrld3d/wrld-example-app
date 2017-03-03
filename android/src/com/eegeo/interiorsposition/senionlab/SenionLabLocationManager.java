package com.eegeo.interiorsposition.senionlab;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Context;

import java.util.ArrayList;

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

	public void startUpdatingLocation(final String[] mapKeyArray, final String apiSecret) throws SLIndoorLocationException
    {
		ArrayList<String> mapKeyList = new ArrayList<String>();
		
		for(int i = 0; i < mapKeyArray.length; ++i)
		{
			mapKeyList.add(mapKeyArray[i]);
		}
		
        m_serviceManager.start(mapKeyList, apiSecret);
        bindService();
	}

    public void stopUpdatingLocation() throws SLIndoorLocationException
    {
        unbindService();
        m_serviceManager.stop();
        
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
    
    private void showConnectionDialog(String Title, String message)
    {
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
    }
}
