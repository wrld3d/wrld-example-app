package com.eegeo;

public interface INativeMessageRunner
{
	void runOnNativeThread(Runnable runnable);
}
