package com.eegeo.examples.examplecontroller;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class SelectNextExampleOnClickListener extends NativeThreadOnClickHandler
{
	public SelectNextExampleOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		ExampleControllerJniMethods.ActivateNext(m_nativeCallerPointer);	
	}
}