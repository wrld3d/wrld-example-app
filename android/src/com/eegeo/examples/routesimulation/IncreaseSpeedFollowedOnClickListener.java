package com.eegeo.examples.routesimulation;


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
	protected void onClickNativeThread() 
	{
		RouteSimulationJniMethods.IncreaseSpeedFollowed(m_nativeCallerPointer);
	}
}