package com.eegeo.examples.routesimulation;


import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ToggleDirectFollowOnClickListener extends NativeThreadOnClickHandler
{
	public ToggleDirectFollowOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RouteSimulationJniMethods.ToggleDirectFollow(m_nativeCallerPointer);
	}
}