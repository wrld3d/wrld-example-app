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
import android.net.wifi.WifiManager;
import android.os.Build;
import android.util.Log;

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
        IntentFilter filter = new IntentFilter();
        filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
        filter.addAction(WifiManager.SUPPLICANT_CONNECTION_CHANGE_ACTION);
        filter.addAction(WifiManager.WIFI_STATE_CHANGED_ACTION);
        m_activity.registerReceiver(networkChangeReceiver, filter, "Manifest.permission.ACCESS_NETWORK_STAT", null);
    }

    void unregisterNetworkChangeReceiver(NetworkChangeReceiver networkChangeReceiver)
    {
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