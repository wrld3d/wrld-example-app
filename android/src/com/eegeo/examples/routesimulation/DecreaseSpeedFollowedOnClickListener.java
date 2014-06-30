package com.eegeo.examples.routesimulation;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class DecreaseSpeedFollowedOnClickListener extends NativeThreadOnClickHandler
{
	public DecreaseSpeedFollowedOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		RouteSimulationJniMethods.DecreaseSpeedFollowed(m_nativeCallerPointer);
	}
}