package com.eegeo.examples.examplecontroller;


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
	protected void onClickNativeThread() 
	{
		ExampleControllerJniMethods.ActivatePrevious(m_nativeCallerPointer);	
	}
}