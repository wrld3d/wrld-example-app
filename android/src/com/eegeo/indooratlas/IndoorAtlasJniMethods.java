package com.eegeo.indooratlas;

public class IndoorAtlasJniMethods 
{
	public static native void OnLocationChanged(long nativeCallerPointer, double latitude, double longitude);
}
