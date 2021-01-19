package com.eegeo.interiorsposition.senionlab;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;

import java.util.ArrayList;
import android.content.Intent;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;

import com.senion.ips.ZoneDetectionApi;
import com.senion.ips.PositioningApi;
import com.senion.ips.SenionIPS.StatusListener;
import com.senion.ips.SenionIPSManager;
import com.senion.ips.SenionIPSHandle;
import com.senion.ips.MapKey;
import com.senion.ips.ApiKey;
import com.senion.ips.Subscription;

public class SenionLabLocationManager
{
    private final MainActivity m_activity;

    private static AlertDialog m_connectionDialog = null;

    private SenionIPSManager m_stepInsideSdkManager;
    private SenionIPSHandle m_stepInsideSdk;
    private ArrayList<Subscription> m_subscriptions = new ArrayList<Subscription>();
    private long m_nativeCallerPointer;
    BluetoothAdapter m_bluetoothAdapter;

    ArrayList<SdkReadyCallback> m_sdkReadyCallbacks = new ArrayList<SdkReadyCallback>();
    private boolean m_isSdkReady = false;

    public SenionLabLocationManager(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    }

    public void askUserToEnableBluetoothIfDisabled()
    {
    	BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		if(m_bluetoothAdapter != null && !m_bluetoothAdapter.isEnabled())
		{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			m_activity.startActivity(enableBtIntent);
		}
    }

    private void onAttachedToSdk(SenionIPSHandle sdk)
    {
        m_stepInsideSdk = sdk;
        m_isSdkReady = true;
        for(SdkReadyCallback callback : m_sdkReadyCallbacks)
        {
            callback.invoke();
        }
        m_sdkReadyCallbacks.clear();
        m_stepInsideSdk.start();

    }

    private final SenionIPSManager.AttachCallback attachCallback = new SenionIPSManager.AttachCallback()
    {
        public void onAttached(SenionIPSHandle sdk) {
            if (m_activity.isDestroyed()) return;
            onAttachedToSdk(sdk);
        }
    };

    public void startUpdatingLocation(final String mapKey, final String apiSecret)
    {
        ArrayList<MapKey> mapKeyList = new ArrayList<MapKey>();

        mapKeyList.add(new MapKey(mapKey));

        m_stepInsideSdkManager = new SenionIPSManager.Builder(getContext())
                .withApiKey(new ApiKey(apiSecret))
                .withMapKeys(mapKeyList)
                .build();

        m_stepInsideSdkManager.initialize();

        m_stepInsideSdkManager.attachHighPerformanceMode(m_activity, attachCallback);
    }

    public void stopUpdatingLocation()
    {

        for (Subscription subscription : m_subscriptions)
        {
            subscription.unsubscribe();
        }

        if (m_stepInsideSdk != null)
        {
            try
            {
                m_stepInsideSdk.stop();
                m_stepInsideSdk.detach();
            }
            catch(Exception e)
            {
                String message = e.getMessage();
                Log.v("SLLocationManager", message == null ? "exception with no message" : message);
            }

            m_isSdkReady = false;
        }

        m_stepInsideSdkManager.terminate();
        if(m_connectionDialog != null)
		{
    		m_connectionDialog.dismiss();
    		m_connectionDialog = null;
		}
    }

    public Subscription registerGeoMessengerReceiver(ZoneDetectionApi.Listener listener)
    {
        Subscription subscription = m_stepInsideSdk.zoneDetection().addListener(listener);
        m_subscriptions.add(subscription);
        return subscription;
    }

    public Subscription registerStatusReceiver(StatusListener listener)
    {
        Subscription subscription = m_stepInsideSdk.addStatusListener(listener);
        m_subscriptions.add(subscription);
        return subscription;
    }

    public Subscription registerPositioningReceiver(PositioningApi.Listener listener)
    {
        Subscription subscription = m_stepInsideSdk.positioning().addListener(listener);
        m_subscriptions.add(subscription);
        return subscription;
    }

    public void unregisterReceiver(Subscription subscription)
    {
        m_subscriptions.remove(subscription);
        subscription.unsubscribe();
    }

    public Context getContext()
    {
        return m_activity.getApplicationContext();
    }


    public interface SdkReadyCallback {
        void invoke();
    }

    public void onSdkReady(SdkReadyCallback callback){
        if(m_isSdkReady)
        {
            callback.invoke();
        }
        else
        {
            m_sdkReadyCallbacks.add(callback);
        }
    }

}
