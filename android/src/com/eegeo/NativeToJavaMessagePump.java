// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo;

import com.eegeo.MainActivity;

public class NativeToJavaMessagePump
{
	public native void pumpNativeMessageQueue(long nativeHandler);

	private MainActivity m_mainActivity;

	public NativeToJavaMessagePump(MainActivity mainActivity)
	{
		this.m_mainActivity = mainActivity;
	}

	public void handleMessage(final long nativeHandler)
	{
		m_mainActivity.runOnUiThread
		(
		    new Runnable()
		{
			public void run()
			{
				pumpNativeMessageQueue(nativeHandler);
			}
		}
		);
	}
}
