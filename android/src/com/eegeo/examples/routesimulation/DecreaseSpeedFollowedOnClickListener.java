package com.eegeo.examples.routesimulation;


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
	protected void onClickNativeThread() 
	{
		RouteSimulationJniMethods.DecreaseSpeedFollowed(m_nativeCallerPointer);
	}
}