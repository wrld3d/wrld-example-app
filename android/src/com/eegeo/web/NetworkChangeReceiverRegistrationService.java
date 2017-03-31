// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.web;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkRequest;
import android.os.Build;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.NativeJniCalls;
import com.eegeo.web.NetworkChangeReceiver;

public class NetworkChangeReceiverRegistrationService
{
    @SuppressLint("NewApi")
    private static class Api21NetworkChangeListener {
        private Activity m_activity;
        private ConnectivityManager.NetworkCallback m_networkCallback;

        Api21NetworkChangeListener(final Activity activity)
        {
            m_activity = activity;
        }

        private void registerOnNetworkAvailableHandler(final String networkChangedIntent)
        {
            if (m_networkCallback != null)
            {
                Log.e("EEGEO", "error: NetworkCallback leaked in registerOnNetworkAvailableHandler.");
            }

            m_networkCallback = new ConnectivityManager.NetworkCallback() {
                @Override
                public void onAvailable(Network network)
                {
                    Intent intent = new Intent();
                    intent.setAction(networkChangedIntent);
                    m_activity.sendBroadcast(intent);
                }
            };
            ConnectivityManager connectivityManager = (ConnectivityManager) m_activity.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkRequest.Builder builder = new NetworkRequest.Builder();
            connectivityManager.registerNetworkCallback(builder.build(), m_networkCallback);
        }

        private void unregisterOnNetworkAvailableHandler()
        {
            ConnectivityManager connectivityManager = (ConnectivityManager) m_activity.getSystemService(Context.CONNECTIVITY_SERVICE);
            connectivityManager.unregisterNetworkCallback(m_networkCallback);
        }
    }

    private Activity m_activity;
    private Api21NetworkChangeListener m_networkChangeListener = null;

    NetworkChangeReceiverRegistrationService(Activity activity)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP)
        {
            m_networkChangeListener = new Api21NetworkChangeListener(activity);
        }
        m_activity = activity;
    }

    void registerNetworkChangeReceiver(NetworkChangeReceiver networkChangeReceiver)
    {
        m_activity.registerReceiver(networkChangeReceiver, new IntentFilter(NetworkChangeReceiver.NETWORK_STATUS_CHANGED_INTENT));
        if (m_networkChangeListener != null)
        {
            m_networkChangeListener.registerOnNetworkAvailableHandler(NetworkChangeReceiver.NETWORK_STATUS_CHANGED_INTENT);
        }
    }

    void unregisterNetworkChangeReceiver(NetworkChangeReceiver networkChangeReceiver)
    {
        if (m_networkChangeListener != null)
        {
            m_networkChangeListener.unregisterOnNetworkAvailableHandler();
        }
        m_activity.unregisterReceiver(networkChangeReceiver);
    }

    int getInitialNetworkStatus()
    {
        return ConnectivityQuerier.getConnectivityStatus(m_activity);
    }
	String getInitialNetworkWifiSSID()
	{
		return WifiSSIDQuerier.getWifiSSID(m_activity);
	}
}