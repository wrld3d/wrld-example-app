// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.web;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.web.ConnectivityQuerier;
import com.eegeo.web.ConnectivityServiceJniMethods;

public class NetworkChangeReceiver extends BroadcastReceiver
{
	public static String NETWORK_STATUS_CHANGED_INTENT = "com.eegeo.web.NETWORK_STATUS_CHANGED";
	protected long m_nativeCallerPointer;
	private MainActivity m_activity;

	public NetworkChangeReceiver(Activity activity, long nativeCallerPointer)
	{
		m_activity = (MainActivity)activity;
		m_nativeCallerPointer = nativeCallerPointer;
	}
	
	@Override
	public void onReceive(Context context, Intent intent) 
	{
		final Context localContext = context;
		m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				final int networkStatus = ConnectivityQuerier.getConnectivityStatus(localContext);
				final String ssid = networkStatus == ConnectivityQuerier.WIFI ? WifiSSIDQuerier.getWifiSSID(localContext) : "";
				ConnectivityServiceJniMethods.SetConnectivityType(m_nativeCallerPointer, networkStatus, ssid);
			}
		});
	}
}
