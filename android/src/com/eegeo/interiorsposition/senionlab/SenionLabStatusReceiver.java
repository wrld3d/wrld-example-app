package com.eegeo.interiorsposition.senionlab;

import android.support.annotation.NonNull;

import com.senion.stepinside.sdk.StepInsideSdk;
import com.senion.stepinside.sdk.StepInsideSdkError;

class SenionLabStatusReceiver extends StepInsideSdk.StatusListener
{
    private SenionLabBroadcastReceiver m_broadcastReceiver;

    public SenionLabStatusReceiver(SenionLabBroadcastReceiver broadcastReceiver)
    {
        m_broadcastReceiver = broadcastReceiver;
    }

    @Override
    public void onError(@NonNull StepInsideSdkError error)
    {
        m_broadcastReceiver.didLocationError(true);
    }
}
