package com.eegeo.examples.placejump;

import android.widget.Spinner;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class VisitButtonOnClickListener extends NativeThreadOnClickHandler
{
	Spinner m_spinner;
	
	public VisitButtonOnClickListener(
			Spinner spinner,
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
		m_spinner = spinner;
	}

	@Override
	protected void onClickNativeThread() 
	{
		final String selection = (String)m_spinner.getSelectedItem();
		PlaceJumpMenuJniMethods.VisitLocation(m_nativeCallerPointer, selection);
	}
}