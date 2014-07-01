package com.eegeo.examples.themereaderwriter;

import android.widget.Spinner;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class SetThemeOnClickListener extends NativeThreadOnClickHandler
{
	Spinner m_spinner;
	
	public SetThemeOnClickListener(
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
		ThemeReaderWriterJniMethods.SetCurrentTheme(m_nativeCallerPointer, selection);
	}
}