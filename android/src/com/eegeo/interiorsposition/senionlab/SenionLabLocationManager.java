package com.eegeo.interiorsposition.senionlab;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;

import java.util.ArrayList;
import android.content.Intent;

import com.eegeo.entrypointinfrastructure.MainActivity;

import com.senion.stepinside.sdk.GeoMessengerApi;
import com.senion.stepinside.sdk.PositioningApi;
import com.senion.stepinside.sdk.StepInsideSdk.StatusListener;
import com.senion.stepinside.sdk.StepInsideSdkManager;
import com.senion.stepinside.sdk.StepInsideSdkHandle;
import com.senion.stepinside.sdk.MapKey;
import com.senion.stepinside.sdk.ApiKey;
import com.senion.stepinside.sdk.Subscription;

public class SenionLabLocationManager
{
    private final MainActivity m_activity;

    private static AlertDialog m_connectionDialog = null;

    private StepInsideSdkManager m_stepInsideSdkManager;
    private StepInsideSdkHandle m_stepInsideSdk;
    private ArrayList<Subscription> m_subscriptions = new ArrayList<Subscription>();
    private long m_nativeCallerPointer;

    ArrayList<SdkReadyCallback> m_sdkReadyCallbacks = new ArrayList<SdkReadyCallback>();
    private boolean m_isSdkReady = false;

    public SenionLabLocationManager(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    public void askUserToEnableBluetoothIfDisabled()
    {
    	BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		if(bluetoothAdapter != null && !bluetoothAdapter.isEnabled())
		{
			Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			m_activity.startActivity(enableBtIntent);
		}
    }

    private void onAttachedToSdk(StepInsideSdkHandle sdk){
        m_stepInsideSdk = sdk;
        m_isSdkReady = true;
        for(SdkReadyCallback callback : m_sdkReadyCallbacks){
            callback.invoke();
        }
        m_sdkReadyCallbacks.clear();
        m_stepInsideSdk.start();
    }

    private final StepInsideSdkManager.AttachCallback attachCallback = new StepInsideSdkManager.AttachCallback() {
        public void onAttached(StepInsideSdkHandle sdk) {
            if (m_activity.isDestroyed()) return;
            onAttachedToSdk(sdk);
        }
    };

    public void startUpdatingLocation(final String[] mapKeyArray, final String apiSecret)
    {
        ArrayList<MapKey> mapKeyList = new ArrayList<MapKey>();

        for(int i = 0; i < mapKeyArray.length; ++i)
        {
            mapKeyList.add(new MapKey(mapKeyArray[i]));
        }

        m_stepInsideSdkManager = new StepInsideSdkManager.Builder(getContext())
                .withApiKey(new ApiKey(apiSecret))
                .withMapKeys(mapKeyList)
                .build();

        m_stepInsideSdkManager.initialize();

        m_stepInsideSdkManager.attachForeground(m_activity, attachCallback);
    }

    public void stopUpdatingLocation()
    {
        if (m_stepInsideSdk != null) {
            m_stepInsideSdk.stop();
            m_stepInsideSdk.detach();
            m_isSdkReady = false;
        }

        for (Subscription subscription : m_subscriptions) {
            subscription.unsubscribe();
        }

        m_stepInsideSdkManager.terminate();
        
        if(m_connectionDialog != null)
		{
    		m_connectionDialog.dismiss();
    		m_connectionDialog = null;
		}
    }

    public Subscription registerGeoMessengerReceiver(GeoMessengerApi.Listener listener)
    {
        Subscription subscription = m_stepInsideSdk.geoMessenger().addListener(listener);
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
        if(m_isSdkReady){
            callback.invoke();
        }
        else{
            m_sdkReadyCallbacks.add(callback);
        }
    }

}
