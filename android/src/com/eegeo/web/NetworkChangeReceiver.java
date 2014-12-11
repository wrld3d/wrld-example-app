package com.eegeo.web;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.eegeo.web.ConnectivityQuerier;
import com.eegeo.web.ConnectivityServiceJniMethods;

public class NetworkChangeReceiver extends BroadcastReceiver
{
	public static String NETWORK_STATUS_CHANGED_INTENT = "com.eegeo.web.NETWORK_STATUS_CHANGED";
	protected long m_nativeCallerPointer;

	public NetworkChangeReceiver(long nativeCallerPointer)
	{
		m_nativeCallerPointer = nativeCallerPointer;
	}
	
	@Override
	public void onReceive(Context context, Intent intent) 
	{
		int networkStatus = ConnectivityQuerier.getConnectivityStatus(context);
		ConnectivityServiceJniMethods.SetConnectivityType(m_nativeCallerPointer, networkStatus);
	}
}
