package com.eegeo.examples.routesimulation;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class IncreaseSpeedFollowedOnClickListener extends NativeThreadOnClickHandler
{
	public IncreaseSpeedFollowedOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		RouteSimulationJniMethods.IncreaseSpeedFollowed(m_nativeCallerPointer);
	}
}