package com.eegeo.web;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import com.eegeo.web.NetworkChangeReceiver;

public class NetworkChangeReceiverProxy extends BroadcastReceiver
{	
	@Override
	public void onReceive(Context context, Intent intent) 
	{
        Intent intentToBroadcast = new Intent();
        intentToBroadcast.setAction(NetworkChangeReceiver.NETWORK_STATUS_CHANGED_INTENT);
        
        context.sendBroadcast(intentToBroadcast); 
	}
}
