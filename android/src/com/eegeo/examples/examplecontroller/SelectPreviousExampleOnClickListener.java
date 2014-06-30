package com.eegeo.examples.examplecontroller;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class SelectPreviousExampleOnClickListener extends NativeThreadOnClickHandler
{
	public SelectPreviousExampleOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		ExampleControllerJniMethods.ActivatePrevious(m_nativeCallerPointer);	
	}
}