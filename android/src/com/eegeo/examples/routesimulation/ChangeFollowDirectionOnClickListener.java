package com.eegeo.examples.routesimulation;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ChangeFollowDirectionOnClickListener extends NativeThreadOnClickHandler
{
	public ChangeFollowDirectionOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		RouteSimulationJniMethods.ChangeFollowDirection(m_nativeCallerPointer);
	}
}