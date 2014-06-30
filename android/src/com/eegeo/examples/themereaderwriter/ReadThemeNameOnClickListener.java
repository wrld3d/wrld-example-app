package com.eegeo.examples.themereaderwriter;

import android.view.View;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ReadThemeNameOnClickListener extends NativeThreadOnClickHandler
{
	public ReadThemeNameOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread(View v) 
	{
		ThemeReaderWriterJniMethods.ReadCurrentThemeName(m_nativeCallerPointer);
	}
}