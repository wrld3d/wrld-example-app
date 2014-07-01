package com.eegeo.examples.routesimulation;


import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ToggleSideOfRoadToDriveOnOnClickListener extends NativeThreadOnClickHandler
{
	public ToggleSideOfRoadToDriveOnOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RouteSimulationJniMethods.ToggleSideOfRoadToDriveOn(m_nativeCallerPointer);
	}
}