package com.eegeo.web;

import android.app.Activity;
import android.content.IntentFilter;

import com.eegeo.web.NetworkChangeReceiver;

public class NetworkChangeReceiverRegistrationService 
{
	private Activity m_activity;
	
	NetworkChangeReceiverRegistrationService(Activity activity)
	{
		m_activity = activity;
	}
	
	void registerNetworkChangeReceiver(NetworkChangeReceiver networkChangeReceiver)
	{
		m_activity.registerReceiver(networkChangeReceiver, new IntentFilter(NetworkChangeReceiver.NETWORK_STATUS_CHANGED_INTENT));
	}
	
	void unregisterNetworkChangeReceiver(NetworkChangeReceiver networkChangeReceiver)
	{
		m_activity.unregisterReceiver(networkChangeReceiver);
	}
	
	int getInitialNetworkStatus()
	{
		return ConnectivityQuerier.getConnectivityStatus(m_activity);
	}
}