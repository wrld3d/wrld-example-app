package com.eegeo.web;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class ConnectivityQuerier 
{
	public static int NOT_CONNECTED = 1;
	public static int WIFI = 2;
	public static int MOBILE = 3;

	public static int getConnectivityStatus(Context context)
	{
		ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
		
		if (activeNetwork != null)
		{
			if (activeNetwork.getType() == ConnectivityManager.TYPE_WIFI)
			{
				return WIFI;
			}
			
			if (activeNetwork.getType() == ConnectivityManager.TYPE_MOBILE)
			{
				return MOBILE;
			}
		}
		
		return NOT_CONNECTED;
	}
}