package com.eegeo.examples.routematching;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ToggleRouteMatchingOnClickListener extends NativeThreadOnClickHandler
{
	public ToggleRouteMatchingOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		RouteMatchingJniMethods.ToggleRouteMatching(m_nativeCallerPointer);
	}
}