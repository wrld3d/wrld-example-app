package com.eegeo.web;

import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

public class WifiSSIDQuerier
{
    public static String getWifiSSID(Context context)
    {
        WifiManager wifiManager = (WifiManager) context.getSystemService (Context.WIFI_SERVICE);
        WifiInfo info = wifiManager.getConnectionInfo();

        if(info == null)
        {
            return "";
        }

        return info.getSSID();
    }
}
