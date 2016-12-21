package com.eegeo.senion;

public class SenionLabLocationJniMethods 
{
	public static native void OnLocationChanged(long nativeCallerPointer, double latitude, double longitude, String floorNo);
}
