package com.eegeo.examples;

import android.view.View;
import android.view.View.OnClickListener;

import com.eegeo.INativeMessageRunner;

public abstract class NativeThreadOnClickHandler implements OnClickListener
{
	protected INativeMessageRunner m_nativeMessageRunner;
	protected long m_nativeCallerPointer;
	
	public NativeThreadOnClickHandler(
			INativeMessageRunner nativeMessageRunner,
			long nativeCallerPointer)
	{
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
	}
	
	@Override
	public void onClick(View v) 
	{
		final View _v = v;
		m_nativeMessageRunner.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				onClickNativeThread(_v);
			}
		});
	}
	
	protected abstract void onClickNativeThread(View v);
}